package main

import(
	"fmt"
	"regexp"
)

func main(){
	str := "Lubie placki"
	reg := regexp.MustCompile("^Lu.+")
	reg2, err := regexp.Compile("(?i)L")

	fmt.Println(reg.FindString(str))
	fmt.Println(reg.MatchString(str))

	if err != nil{
		fmt.Println(err)
	} else {
		fmt.Println(reg2.ReplaceAllString(str, "asdf"))
	}
}
