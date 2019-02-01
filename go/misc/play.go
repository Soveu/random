package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func properSplit(data []byte, atEOF bool) (advance int, token []byte, err error) {
	inString := false
	index := 0
	wasWhite := false

	for i, c := range data {
		if c == ' ' || c == '\n' || c == '\t' {
			if wasWhite || inString {
				continue
			} else {
				wasWhite = true
				index = i
			}
		} else if wasWhite {
			return i, data[:index], nil
		}
		if c == '"' {
			if inString {
				return i + 1, data[:i+1], nil
			}
			inString = true
		}
		if inString {
			continue
		}
	}

	return 0, data, bufio.ErrFinalToken
}
func splitter(in string) []string {
	scanner := bufio.NewScanner(strings.NewReader(in))
	scanner.Split(properSplit)
	out := make([]string, 0, 5)

	for scanner.Scan() {
		out = append(out, scanner.Text())
	}

	return out
}

func xdxd() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Enter command: ")
	in, _ := reader.ReadString('\n')

	output := splitter(in)

	for i, item := range output {
		fmt.Printf("%d: '%s'\n", i, item)
	}
}

func main() {
	xdxd()
}
