package main

import(
	"fmt"
	"math/cmplx"
)

const(
	dataLen = 32
)
func main(){
	a := complex(0.0, 2.0)
	b := complex(0.0, 0.0)

	for i := -32; i<=32; i++ {
		num := complex(float64(i) - real(a), imag(a))
		res := cmplx.Pow(num, 2) + b
		fmt.Printf("%f %fi\t %v\n", real(res), imag(res), i*i)
	}
}
