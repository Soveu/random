package main

import(
	"fmt"

	"github.com/spy16/parens"
)

func main(){
	cmds := []string{"(print (add 2 3 5))", "pi"}
	scope := parens.NewScope(nil)
	scope.Bind("add", func(nums... int64) (res int64){
		for _, num := range nums{
			res += num
		}
		return
	})
	scope.Bind("print", fmt.Println)
	scope.Bind("pi", 3.14)

	exec := parens.New(scope)

	for _, cmd := range cmds{
		val, err := exec.Execute(cmd)
		if err != nil{
			fmt.Println(err)
		}
		fmt.Println(val)
	}
}
