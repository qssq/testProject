package main

import "fmt"

func main() {
	a := 100.0
	b := 20.0
	c := 50.0
	d := (a + b + c) * (1.0 - 0.05)

	aa := 0.0
	bb := 0.0
	cc := 0.0

	//a * aa + b + c = d
	//a + b * bb + c = d
	//a + b + c * cc = d
	aa = (d - b -c) / a
	bb = (d - a -c) / b
	cc = (d - b -a) / c

	fmt.Printf("aa:%0.2f\n", aa)
	fmt.Printf("bb:%0.2f\n", bb)
	fmt.Printf("cc:%0.2f\n", cc)
}

type IResult interface {
	GetTitle() string
}

type Result struct {
	Ddds  float64
	Total float64
}

type Match struct {
	Team1 IResult
	Team2 IResult
}

func (match *Match) UpdateDdds() {

}
