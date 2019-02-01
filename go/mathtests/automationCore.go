package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"mime/multipart"
	"net/http"
	"net/http/cookiejar"
	"os"
	"strings"
	"time"

	"github.com/PuerkitoBio/goquery"
)

// adding headers used by firefox on Linux with English language
func addFakeHeaders(req *http.Request) {
	req.Header.Set("User-Agent",
		"Mozilla/5.0 (X11; Linux x86_64; rv:64.0) Gecko/20100101 Firefox/64.0")
	req.Header.Set("Referer", "http://212.59.241.225/arkusze/login.php")
	req.Header.Set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8")
	req.Header.Set("Accept-Language", "en-US,en;q=0.5")
	req.Header.Set("Accept-Encoding", "gzip, deflate")
	req.Header.Set("Connection", "keep-alive")
	req.Header.Set("Upgrade-Insecure-Requests", "1")
}

func getGuestCridentials(jar *cookiejar.Jar) ([]string, error) {
	// create client
	client := &http.Client{
		Jar: jar,
	}

	//get the login page
	resp, err := client.Get(myURL + "login.php")
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	// parse login page
	doc, err := goquery.NewDocumentFromReader(resp.Body)
	if err != nil {
		return nil, err
	}
	var logD []string
	// find non empty login fields
	doc.Find(".login-haslo").Each(func(i int, s *goquery.Selection) {
		data, is := s.Attr("value")
		if is && data != "" {
			logD = append(logD, data)
		}
	})
	return logD, err
}

func getCookie() (*cookiejar.Jar, error) {
	// create an empty jar and a client with it
	jar, _ := cookiejar.New(nil)
	client := &http.Client{
		Jar: jar,
	}

	//ping the homepage to start a session and get the cookie
	resp, err := client.Get(myURL + "index.php")
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	return jar, nil

}

func logIn(jar *cookiejar.Jar, credentials []string) error {
	// create base form data
	body := &bytes.Buffer{}
	writer := multipart.NewWriter(body)

	// add login field
	loginD, err := writer.CreateFormField("username")
	if err != nil {
		return err
	}
	loginD.Write([]byte(credentials[0]))

	// add password field
	passwordD, err := writer.CreateFormField("password")
	if err != nil {
		return err
	}
	passwordD.Write([]byte(credentials[1]))

	// add special field
	mysteryD, err := writer.CreateFormField("send_login")
	if err != nil {
		return err
	}
	mysteryD.Write([]byte("1"))

	// add upload field
	uploadD, err := writer.CreateFormField("upload")
	if err != nil {
		return err
	}
	uploadD.Write([]byte("Zaloguj mnie"))

	//create the request
	writer.Close()
	req, err := http.NewRequest("POST", myURL+"login.php", body)
	if err != nil {
		return err
	}
	req.Header.Set("Content-Type", writer.FormDataContentType())
	// add masking headers
	addFakeHeaders(req)

	//send request
	client := &http.Client{
		Jar: jar,
	}
	_, err = client.Do(req)
	return err

}

func parseTerst(name string, jar *cookiejar.Jar) error {

	// Create client
	client := &http.Client{
		Jar: jar,
	}
	// get the report page
	resp, err := client.Get(myURL + "raport.php?nazwa_testu=" + name)
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	// parse the source
	doc, err := goquery.NewDocumentFromReader(resp.Body)
	if err != nil {
		log.Fatal(err)
		return err
	}

	// find the data `stream`
	body := doc.Find("#cialo-strony")
	// nessecary variables
	flag := false
	var currentExercise exercise
	var currentSub subExercise
	myTest := test{}
	// for all entries
	body.Children().Each(func(i int, s *goquery.Selection) {
		// discard vanity nodes
		_, is := s.Attr("style")
		if is {
			return
		}
		// get the class
		cls, is := s.Attr("class")
		// discard not taggend nodes if flag not raised
		if !is && !flag {
			return
		}
		// find standardised questions answers
		if flag && cls == "" {
			cls = "odpowiedziZ"
			flag = false
		}

		// react properly to different nodes
		switch cls {
		case "nag_pytania":
			// add preovius question to the test if not first time
			if currentExercise.Name != "" {
				myTest.Questions = append(myTest.Questions, currentExercise)
			}
			// start new question
			currentExercise = exercise{
				HasVariables: false,
			}
			//set question name
			s.Find("td").Each(func(i int, ss *goquery.Selection) {
				if i == 1 {
					currentExercise.Name = ss.Text()[17:]
				}
			})
		case "nag_podpunkt":
			// create new sub
			currentSub = subExercise{
				Number:       s.Text()[len(s.Text())-1:],
				HasVariables: false,
			}
		case "tresc":
			return
		case "nag_dane":
			currentSub.HasVariables = true
			currentExercise.HasVariables = true
		case "dane":
			// create a map of all question variables
			data := make(map[string]string)
			rows := strings.Split(s.Text(), "\n")
			for _, row := range rows {
				if row != "" {
					sliced := strings.Split(row, "=")
					data[sliced[0]] = sliced[1]
				}

			}
			// add variable data to sub
			currentSub.Variables = data

		case "nag_odpowiedzi":
			// not ignore the next untagged node
			flag = true
		case "odpowiedzi":
			// start ignoring unnesecary nodes
			flag = false
			// find the correct answer field and add it's value
			s.Find("td").Each(func(i int, ss *goquery.Selection) {
				st, is := ss.Attr("style")
				if !is {
					return
				}
				if st == "border: 1px solid #44cc44; background: #ccffcc" && i == 4 {
					currentSub.Answer = ss.Text()
					currentExercise.Subs = append(currentExercise.Subs, currentSub)
				}
			})
		case "odpowiedziZ":
			// find trhe correct answer of a closed question
			s.Find("div").Each(func(i int, ss *goquery.Selection) {
				sty, _ := ss.Attr("style")
				if sty == "border: 1px solid #44cc44; background: #ccffcc" && i > 3 {
					spn := ss.Find("img")
					if len(spn.Nodes) == 1 {
						alt, _ := spn.Attr("alt")
						currentSub.Answer = alt
						currentExercise.Subs = append(currentExercise.Subs, currentSub)
					} else {
						currentSub.Answer = ss.Text()
						currentExercise.Subs = append(currentExercise.Subs, currentSub)
					}
				}
			})
		default:
			// catch any unexpected nodes
			fmt.Print("Unknown tag ")
			fmt.Println(cls)
		}
	})
	// add the last question
	myTest.Questions = append(myTest.Questions, currentExercise)

	//save to json
	js, err := os.Create(name + ".json")
	if err != nil {
		log.Fatal(err)
		return err
	}
	defer js.Close()
	enc := json.NewEncoder(js)
	enc.Encode(myTest)
	return nil
}

func generateTest(name string, jar *cookiejar.Jar) error {
	// create client
	client := &http.Client{
		Jar: jar,
	}

	// start the test
	resp, err := client.Get(myURL + "generuj_test.php?nazwa_testu=" + name)
	if err != nil {
		return err
	}

	// parse the test
	doc, err := goquery.NewDocumentFromReader(resp.Body)
	if err != nil {
		return err
	}

	// create the response writer
	fBody := &bytes.Buffer{}
	writer := multipart.NewWriter(fBody)

	// add the hidden value
	hidD, err := writer.CreateFormField("nazwa_testu")
	if err != nil {
		return err
	}
	hidD.Write([]byte(name))

	// to prevent multiple choice questions from being added 4 times
	last := ""
	// loop over all input fields and add them to the response
	doc.Find("input").Each(func(i int, s *goquery.Selection) {
		n, _ := s.Attr("name")
		// filtering constant and repeded inputs
		if n == "nazwa_testu" || n == last || n == "" {
			return
		}
		qD, err := writer.CreateFormField(n)
		if err != nil {
			log.Fatal(err)
			return
		}
		qD.Write([]byte("0"))
		last = n
	})
	writer.Close()

	// await for authentic effect
	time.Sleep(30 * time.Minute)

	// create a request
	req, err := http.NewRequest("POST", myURL+"odbierz_test.php", fBody)
	if err != nil {
		return err
	}
	req.Header.Set("Content-Type", writer.FormDataContentType())
	addFakeHeaders(req)

	// send the response
	_, err = client.Do(req)

	return err
}

func getLatest(wantedC string, wanted string, jar *cookiejar.Jar) (string, error) {
	// set nessecary variables and sanirtaze input
	toR := ""
	var wantedL int
	switch wanted {
	case "pp":
		wantedL = 0
	case "pr":
		wantedL = 1
	default:
		return "", nil
	}

	// Create client
	client := &http.Client{
		Jar: jar,
	}

	// getting the data
	resp, err := client.Get(myURL + "arkusze_maturalne.php")
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()

	// parse the source
	doc, err := goquery.NewDocumentFromReader(resp.Body)
	if err != nil {
		log.Fatal(err)
		return "", err
	}

	body := doc.Find(".f-ramka")

	currentClass := ""
	//var latest map[string][]string

	// loop through all nodes
	body.Children().Each(func(i int, s *goquery.Selection) {
		// skip if value found
		if toR != "" {
			return
		}
		// disregard styled nodes
		_, is := s.Attr("style")
		if is {
			return
		}
		// get the current class
		_, is = s.Attr("class")
		if is && s.Text() != "Arkusze maturalne" {
			currentClass = s.Text()[len(s.Text())-1:]
			return
		}

		// find all class tables
		wd, _ := s.Attr("width")
		if wd == "100%" {
			// reset class specific variables
			level := 0
			latestS := make([]string, 2)
			// for all levels
			s.Find("td").Each(func(ii int, ss *goquery.Selection) {
				st, _ := ss.Attr("style")
				if st == "border: 1px solid gray; padding: 10px" {
					newest := ""
					// for all tests
					ss.Find("td").Each(func(iii int, sss *goquery.Selection) {
						wdd, _ := sss.Attr("width")
						if wdd == "70%" {
							newest = sss.Text()
						}
					})
					latestS[level] = newest
					level++
				}
			})
			// return the output
			if currentClass == wantedC {
				toR = latestS[wantedL]
				return
			}

		}

	})
	return toR, err
}

func saveToDatabase(path string) error {
	// create the database as a map
	dataB := make(map[string][]exercise)

	// read data if any exists
	dataF, err := os.Open("DATA.json")
	if err == nil {
		byteD, _ := ioutil.ReadAll(dataF)
		json.Unmarshal(byteD, &dataB)

	}
	dataF.Close()

	// get the new tests file
	file, err := os.Open(path)
	if err != nil {
		return err
	}
	defer file.Close()

	// read the file and turn it back into a struct
	byteVal, _ := ioutil.ReadAll(file)
	var test2 test
	json.Unmarshal(byteVal, &test2)

	// compare data sest
	for _, q := range test2.Questions {
		// check if name appears in database
		if saved, ok := dataB[q.Name]; ok {
			// set flags
			questionIsVariable := true
			variablilityFlag := 0
			// for each saved question variant
			for _, savedQuestion := range saved {
				// skip unchangable questions
				if !savedQuestion.HasVariables {
					questionIsVariable = false
					continue
				}
				// for all subs
				for subID, sub := range savedQuestion.Subs {
					subIsDuplicate := false
					if !sub.HasVariables {
						continue
					}
					// if values don't mach set flag
					for key, val := range sub.Variables {
						if q.Subs[subID].Variables[key] != val {
							subIsDuplicate = true
						}
					}
					// if duplicate increment the duplicate counter
					if !subIsDuplicate {
						variablilityFlag++
					}
				}
			}
			// if there is a possiblility of change
			if questionIsVariable {
				// if no dubles add
				if variablilityFlag == 0 {
					fmt.Println("adding")
					saved = append(saved, q)
					dataB[q.Name] = saved
				}
			}
		} else {
			// add new questions
			if q.Name != "" {
				qq := []exercise{q}
				dataB[q.Name] = qq
			}
		}
	}

	// save end result to disk
	dataBF, err := os.Create("DATA.json")
	if err != nil {
		return err
	}
	defer dataBF.Close()
	enc := json.NewEncoder(dataBF)
	enc.Encode(dataB)
	return err

}
