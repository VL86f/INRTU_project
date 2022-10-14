// test project main.go
package main

import (
	"fmt"
	"io"
	"os"
	"bufio"
	"strconv"
	"math"
	"strings"
	"time"
)

func dec_to_hex (variable, recom int) []byte {
	var hex string = ""
	var exa string = "0123456789ABCDEF"
	for x := variable; x>0;  {
			y := x % 16
			hex = string(exa[y]) + hex
			x = x / 16
	}	
	var chisl int = len(hex)
	//var le int = int(chisl / 2) + chisl % 2
	ch := make([]string, 0)
	ans := make([]byte, 0)
	for x := chisl-1;x>=0; {
		chis := string(hex[x])
		if x-1>=0 {
			chis = string(hex[x-1]) + chis
		}
		ch = append(ch, chis)
		x = x-2
	}	
	chisl = len(ch)
	var i int
	for x := 0; x<chisl; x++ {
		w := 0
		od := ch[x]
		for y := 0;y<len(od);y++ {
			switch(string(od[y])) {
			case "A": i = 10
			case "B": i = 11
			case "C": i = 12
			case "D": i = 13
			case "E": i = 14
			case "F": i = 15
			default: 
				z, err := strconv.Atoi(string(od[y]))
				if err != nil {
					panic(err)
					bufio.NewReader(os.Stdin).ReadBytes('\n')
					os.Exit(5)
				}
				i = z
			}
			w = w + i * int(math.Pow(16, float64(len(od)-1-y)))
		}	
		ans = append(ans, byte(w))
	}	

	if len(ans)<recom {
		df := recom-len(ans)
		for i := 0;i < df;i++ {
			ans = append(ans, 00)
		}	
	}	
	return ans[:]
	
}	


func main() {

	var name string
	fmt.Println("Name?")
	fmt.Scanln(&name)
	var height,width int
	fmt.Println("Enter width and height")
	fmt.Scan(&width, &height)
	fmt.Println("Attention. This is test programm")
	fmt.Printf("width and height: %dx%d\n", width, height)
	file, err := os.Open(name)
	if err != nil {
		panic(err)
		os.Exit(1)
	}
	defer file.Close() 
	var time1 int64 = time.Now().Unix()
	name = strings.ReplaceAll(name, ".txt", ".bmp")
	 file2 ,err1 := os.Create(name)
	if err1 != nil {
		panic(err1)
		os.Exit(1)
	}	
	defer file2.Close() 
	var size int = height * width * 3 + 54
	//fmt.Println(size)
	head := make([]byte, 0)
	out := make([]byte, 0)
	read := make([]byte, 1024)
	head = append(head, 66,77)
	
	size_out := dec_to_hex(size, 4)
	head = append(head, size_out[:]...)
	head = append(head, 00,00,00,00,54,00,00,00,40,00,00,00)
	width_out := dec_to_hex(width, 4)
	height_out := dec_to_hex(height, 4)
	head = append(head, width_out[:]...)
	head = append(head, height_out[:]...)
	head = append(head, 01,00,24)
	for i := 0;i < 25;i++ {
			head = append(head, 00)
		}
	readed := make([]byte, 0)
	for ;true; {
		wri, err := file.Read(read)
		if err == io.EOF { // если конец файла
			break // выходим из цикла
		}
		readed = append(readed, read[:wri]...)
	}
		/*for x := 0;x < 16;x++ {
		//y := width*height*3-1-x
		fmt.Print(" ", string(readed[x]))
		}*/
	var blok byte = 0
	for i := 0;i<len(readed);i++{
		cif := readed[i] 
		switch(string(cif)) {
			case " ":	
				out = append(out, blok)
				//fmt.Println("blok: ", blok)
				blok = 0
			case ";":
				blok = 0
			case "\n":
				continue
			case "0":
				blok = blok * 10
			default:
				z, err := strconv.Atoi(string(cif))
				if err != nil {
					panic(err)
					bufio.NewReader(os.Stdin).ReadBytes('\n')
					os.Exit(5)
				}
				blok = blok * 10 + byte(z)
		}	
	}	
	cout := make([]byte, 0)
	var compl int = width % 4
	var wi = width
//	var he = height-1
	for x := 0;x < height*width*3; {
		cout = append(cout, out[x+2])
		cout = append(cout, out[x+1])
		cout = append(cout, out[x])
		x = x + 3
		wi--
		if wi <=0 {
			for z := 0;z<compl;z++ {
				cout = append(cout, 0)
			}
		wi = width
//		he--
		}	
	}	
	file2.Write(head)
	file2.Write(cout)
	//test := []byte{0,1,2,3}
	//file2.Write(test)
	time1 = time.Now().Unix() - time1
	fmt.Printf("Time: %d h, %d m, %d s\n", time1/3600, (time1%3600)/60, time1%60)
	fmt.Print("END.\nPress Enter for close programm\n")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}
