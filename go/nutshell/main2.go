package main

import (
	"fmt"
	"strings"
)

type IOFunc func([]string)string
const MSG = "$ say Hello $VAR "

func main() {

	funcMap := map[string] (func([]string)string){
		"say": func(in []string) string{
			return strings.Join(in, " ")
		},
	}


	var (
		out	string
	)

	if strings.HasPrefix(MSG, "$ ") {
		s := Split(MSG[2:])

		fmt.Println(s)

		f, ok := funcMap[s[0]]

		if ok {
			out = f(s[1:])
		} else {
			out = "Function not found"
		}
	} else {
		out = "Error"
	}

	fmt.Println(out)
}
