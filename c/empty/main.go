package main

import "fmt"

type Nothing struct {}

func main(){
  var n1 Nothing
  var n2 Nothing
  var num int64

  fmt.Printf("%X %X %X\n", &n1, &n2, &num)
  fmt.Printf("%v %v %v\n", n1, n2, num)
}

