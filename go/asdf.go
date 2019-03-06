package main

import "fmt"

var test = []int{1,2,3}

func main() {
    appendTest(4, 5, 6)
    appendTest(7, 8, 9)
}

func appendTest(ints... int) {
    test = append(test, ints...)
    fmt.Println(test)
}
