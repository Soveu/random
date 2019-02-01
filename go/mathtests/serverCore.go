package main

import (
	"encoding/json"
	"html/template"
	"io/ioutil"
	"net/http"
	"os"
)

type postData struct {
	QiD     string
	Results []exercise
}

func dynamicHandler(w http.ResponseWriter, r *http.Request) {
	tmpl := template.Must(template.ParseFiles("templates/index.html"))
	if r.Method == http.MethodGet {
		tmpl.Execute(w, nil)
	} else if r.Method == http.MethodPost {
		data := postData{
			QiD: r.FormValue("q_id") + "\n",
		}
		dataB := make(map[string][]exercise)
		dataBF, err := os.Open("DATA.json")
		if err != nil {
			http.Error(w, "Internal Server error", http.StatusInternalServerError)
			return
		}
		byteDB, _ := ioutil.ReadAll(dataBF)
		json.Unmarshal(byteDB, &dataB)
		dataBF.Close()

		data.Results = dataB[data.QiD]
		tmpl.Execute(w, data)
		//fmt.Fprint(w, "POST")
	} else {
		http.Error(w, "What exacly are you doing here?", http.StatusBadRequest)
	}
}

func coffeHandler(w http.ResponseWriter, r *http.Request) {
	http.Error(w, "I'm just a teapot. I can't brew coffee", http.StatusTeapot)
}

func httpDeamon() {
	http.HandleFunc("/", dynamicHandler)
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))
	http.HandleFunc("/coffee/", coffeHandler)
	http.ListenAndServe(":8080", nil)
}
