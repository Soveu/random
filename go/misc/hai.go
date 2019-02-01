package main

import (
	"fmt"
	"time"
)

func printer(c chan string, e chan bool) {
	for str := range c {
		for _, char := range str {
			fmt.Print(string(char))
			time.Sleep(time.Millisecond * 200)
		}
	}

	e <- true
}

func main() {
	c := make(chan string)
	e := make(chan bool)
	go printer(c, e)
	c <- "Hello "
	c <- "World!"
	close(c)
	<-e
}
