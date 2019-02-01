package main

import "fmt"

type Test struct {
  elems []string
}

func main() {
  initial := Test{
    elems: make([]string, 0),
  }
  initial.elems = append(initial.elems, "apple")
  fmt.Println(initial.elems) // #1 [apple]

  s := make([]Test, 0)
  s = append(s, initial)

  initial.elems = append(initial.elems, "bannana")
  fmt.Println(initial.elems) // #2 [apple bannana]
  fmt.Println(s[0].elems) // #3 [apple]

  second := s[0]
  second.elems = append(second.elems, "carrot")
  fmt.Println(second.elems) // #4 [apple bannana]

  fmt.Printf("second: %p, initial: %p\n", &second.elems[0], &initial.elems[0])
}
