package main

import(
	"fmt"
	"bufio"
	"strings"
)

const(
	TYPE_KEYWORD = 0
	TYPE_FUNC = 1
	TYPE_STRING_WEAK = 2
	TYPE_STRING = 3
	TYPE_VAR = 4
)

type parsedWord struct{
	str string
	num uint16
	typ uint8
}

chanToMaker := make(chan parsedWord, 127)
chanError := make(chan error, 1)

scrip := map[rune]func(s string, c uint){
	'"':	func(s string, c uint){
			st = s[1:]
			stopIndex = strings.IndexByte(st, '"')
			toMaker <- parsedWord{
				str: st[:stopIndex],
				num: c,
				typ: TYPE_STRING
			}

			return stopIndex
		}
	'\'':	func(s string, c uint){
			st = s[1:]
			stopIndex = strings.IndexByte(st, '\'')
			toMaker <- parsedWord{
				str: st[:stopIndex],
				num: c,
				typ: TYPE_STRING
			}

			return stopIndex
		}
	'$':	func(s string, c uint){
			st = s[1:]


		}
}


func splitter(in string) {
	var(
		inString		bool
		isStrWeak		bool

		startIndex		int
		stopIndex		int

		word			parsedWord
	)
	var counter uint

	for {
		for i,c := range in{
			if !unicode.IsSpace(c) {
				startIndex = i
				break
			}
		}

		noSpaceSlice := in[startIndex:]
		if len(noSpaceSlice) == 0 {
			break
		}

		fun, ok := scrip[noSpaceSlice[0]]

		if ok {
			go fun(noSpaceSlice, counter)
			continue
		} else {
			//do normal parsing stuff
		}

		counter++
	}
}

func parser(in string, order uint){
	fmt.Printf("'%s': %d\n", in, order)
}

func maker(){

}

func main(){
	var input = string("say \"Hello World! \"  to\tMatonix")

	fmt.Println(input)
	splitter(input)
}
