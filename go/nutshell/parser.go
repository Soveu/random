package main

import (
	"strings"
	"unicode"
)

func Split(in string) []string {
	var (
		stopIndex	int
		startIndex	int
	)
	out := make([]string, 0, 8)
	str := in

	for {
		for i, c := range str{
			if !unicode.IsSpace(c) {
				startIndex = i
				break
			}
		}

		noSpaceSlice := str[startIndex:]
		if len(noSpaceSlice) == 0 {
			break
		}

		switch noSpaceSlice[0] {
		case '"':
			stopIndex = strings.IndexRune(noSpaceSlice[1:], '"') + 1
		case '\'':
			stopIndex = strings.IndexRune(noSpaceSlice[1:], '\'') + 1
		default:
			stopIndex = strings.IndexRune(noSpaceSlice[1:], ' ') + 1
		}

		if stopIndex == 0 {
			out = append(out, noSpaceSlice)
			break
		} else {
			str = str[stopIndex+1:]
			out = append(out, noSpaceSlice[:stopIndex])
		}
	}

	return out
}

