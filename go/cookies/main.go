package main

import (
	"fmt"
	"net/http"
)

var(
  port  string = "8080"
)

func handleFunc(w http.ResponseWriter, r *http.Request){
  cook := http.Cookie{
    Name: "foo",
    Value: "bar",
    MaxAge: 0,
  }

  fmt.Fprint(w, `<html><body>
  <form action="/post" method="POST">
    <input type="text" name="name">
    <input type="text" name="surname">
    <input type="submit" value="Submit">
  </form>
  </body></html>`)

  if _, err := r.Cookie("foo"); err != nil{
    http.SetCookie(w, &cook)
  } else {
    fmt.Fprintln(w, "Your 'foo' cookie is set<br>")
  }

  fmt.Fprintln(w, "Hello<br>")

  return
}

func getCookie(w http.ResponseWriter, r *http.Request){
  cookies := r.Cookies()
  fmt.Fprintf(w, "<html><body>These are your cookies:\n<br>%s<br>\n", cookies)

  for _, cookie := range cookies{
    fmt.Fprintf(w, "<br>\"%s\": \"%s\"\n", cookie.Name, cookie.Value)
  }
  return
}

func getPost(w http.ResponseWriter, r *http.Request){
  err := r.ParseForm()
  if err != nil{
    fmt.Fprintf(w, "An error occured:\n%s\n", err)
    return
  }

  if len(r.PostForm) == 0{
    fmt.Fprint(w, "No post variables sent")
    return
  }

  for k, v := range r.PostForm{
    fmt.Fprintf(w, `<br>"%s": "%s"`, k, v)
  }
  return
}

func main() {
  http.HandleFunc("/", handleFunc)
  http.HandleFunc("/cookie", getCookie)
  http.HandleFunc("/post", getPost)

  fmt.Printf("Serving on port %s\n", port)
  //http.ListenAndServeTLS(fmt.Sprint(":", port), "cert", "key", nil)
  http.ListenAndServe(fmt.Sprint(":", port), nil)
}
