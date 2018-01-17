package main

import (
	"fmt"
	"time"
	"math/rand"
)

func main(){
	var a int = 1
	var b int = 0
	c := a << uint(b)
	fmt.Printf("c=%d", c)
	b = 1
	c = a << uint(b)
	fmt.Printf("c=%d", c)
	b = 2
	c = a << uint(b)
	fmt.Printf("c=%d", c)

	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	for i:=0; i<10; i++ {
		fmt.Println(r.Intn(2))
	}
}


