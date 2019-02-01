package main

import (
	"fmt"
	"log"
	"strconv"
	"time"
)

var myURL = "http://212.59.241.225/arkusze/"

func getTestData() {
	//getting a new cookie and creating a session
	jar, err := getCookie()
	if err != nil {
		fmt.Println("Error getting cookie")
		fmt.Println(err)
		return
	}
	fmt.Println(jar)

	// gettin new cridentials to log in
	cred, err := getGuestCridentials(jar)
	if err != nil {
		fmt.Println("Error getting guest login")
		fmt.Println(err)
		return
	}

	// logging in
	err = logIn(jar, cred)
	if err != nil {
		fmt.Println("Error logging in")
		fmt.Println(err)
		return
	}
	for i := 1; i < 4; i++ {

		//get latest test
		newest, err := getLatest(strconv.Itoa(i), "pr", jar)
		if err != nil {
			fmt.Println("Error getting newest")
			fmt.Println(err)
			return
		}

		err = generateTest(newest, jar)
		if err != nil {
			log.Fatal(err)
			return
		}
		fmt.Println("Test generated")

		err = parseTerst(newest, jar)
		if err != nil {
			log.Fatal(err)
			return
		}

		err = saveToDatabase(newest + ".json")
		if err != nil {
			log.Fatal(err)
			return
		}
		time.Sleep(10 * time.Minute)
	}
}

// TODO add non debugging functionality
func main() {

	//starting the web server
	go httpDeamon()

	for {
		/*getTestData()
		today := time.Now().Weekday()
		switch today {
		case time.Sunday:
			time.Sleep(24 * time.Hour)
		case time.Thursday:
			time.Sleep(time.Hour)
		default:
			tim := time.Now().Hour()
			if tim < 17 {
				time.Sleep(2 * time.Hour)
			} else {
				time.Sleep(10 * time.Hour)
			}

		}*/
	}

}
