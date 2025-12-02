package main

import (
	"fmt"
	"math"
)

func main() {
	for i := range 100000 {
		fmt.Println(uint(math.Floor(math.Log10(float64(i))+1)), i)
	}

}
