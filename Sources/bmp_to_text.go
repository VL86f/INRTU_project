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
func RGB_bit(completion,height,witdh int,name,name_out string,data ...byte) {
	fmt.Println("24_bit Start")
	var comply int = completion * height
	var k int
	name = strings.ReplaceAll(name, name_out, ".txt")
	file2 ,err1 := os.Create(name)
	if err1 != nil {
		panic(err1)
		os.Exit(1)
	}
	defer file2.Close()
	var max_size int = witdh * height
	if height > 0 {
		witdh_out := 0
		for x:=0;x<max_size;x++ {
			if witdh_out == 0{
				if x != 0 {
					_,err := io.WriteString(file2, "\n")
						if err != nil {
							panic(err)
							os.Exit(1)
						}
				}
				witdh_out = witdh
				comply = comply - completion
				k = witdh-1
				}
			//y := (x-k)*3 + comply
			y :=x*3
			z := strconv.Itoa(int(data[y+2])) + " "+ strconv.Itoa(int(data[y+1])) + " " +strconv.Itoa(int(data[y])) + " 255;"
			_,err := io.WriteString(file2, z)
			if err != nil {
				panic(err)
				os.Exit(1)
			}
			witdh_out--
			k = k - 2
		}
	}
	_,err := io.WriteString(file2, "\n")
	if err != nil {
		panic(err)
		os.Exit(1)
	}
}
func dec_to_dec(data ...int) (int) {
	var ran int = len(data)
	var ans int = 0
	var hex string = "0123456789ABCDEF"
	var part string
	var chisl string = ""
	for i:=ran-1;i>=0;i-- {
		part = ""
		if data[i] == 0 {
			part = "00"
		}
		for pr:=data[i];pr>0; {
			x := pr % 16
			part = string(hex[x]) + part
			pr = pr / 16
		}
		chisl = chisl + part
	}
	ran = len(chisl)
	for i:=0;i<ran;i++ {
		x := 0
		switch(string(chisl[i])) {
			case "A": x = 10
			case "B": x = 11
			case "C": x = 12
			case "D": x = 13
			case "E": x = 14
			case "F": x = 15
			default:
				z, err := strconv.Atoi(string(chisl[i]))
				if err != nil {
					panic(err)
					bufio.NewReader(os.Stdin).ReadBytes('\n')
					os.Exit(5)
				}
				x = z

		}
		y := x * int(math.Pow(16, float64(ran-i-1)))
		ans = ans+y
	}
	return ans
}


func main() {

	var name string
	fmt.Println("Name?")
	fmt.Scanln(&name)
	fmt.Println("Attention. This is test programm")
	stri := strings.Split(name, ".")
	k := len(stri)
	var name_out string = "."+stri[k-1]
	file, err := os.Open(name)
	if err != nil {
		panic(err)
		os.Exit(1)
	}
	defer file.Close()

	data := make([]byte, 0)
	buf := make([]byte, 54)
	buf2 := make([]byte, 1024)
	var i int


		wri, err := file.Read(buf)
		if err == io.EOF { // если конец файла
			fmt.Println("File is end")
		}

		data = append(data, buf[:wri]...)

	if len(data) < 53 {
		fmt.Println("Error.Invalid file type or file have very small size")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(3)
	}
	if data[0] != 66 && data[1] != 77 && data[15] != 0 && data[16] != 0 {
		fmt.Println("Error. Invalid file type")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}else if data[14] != 40 && data[14] != 108 && data[14] != 124 {
		fmt.Println("Error. Unsupported file version")
		fmt.Print("Header Version: ")
		fmt.Println(data[14])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}
	fmt.Println("Type of file: passed")
	if data[26] != 1 && data[27] != 0 && data[29] != 0  {
		fmt.Println("Error. Unsupported file version")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	} else if data[28] == 16 || data[28] > 32 {
		fmt.Println("Error. Unsupported color depth")
		fmt.Print("Color depth: ")
		fmt.Println(data[28])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	} else if data[28] <= 8 {
		fmt.Println("Sorry. But this color depth is not supported yet.")
		fmt.Print("Color depth: ")
		fmt.Println(data[28])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)

	} else if data[30] != 0 && data[31] != 0 && data[32] !=0 && data[33] !=0 {
		fmt.Println("Error. Data is compressed or encrypted")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}
	fmt.Println("Support test: passed")
	var bit int = int(data[28])
	var size int = dec_to_dec(int(data[2]),int(data[3]),int(data[4]),int(data[5]))
	fmt.Printf("File of size: %d bytes\n", size)
	var colors int = dec_to_dec(int(data[10]),int(data[11]),int(data[12]),int(data[13]))
	var color_test bool = (size-int(data[14])-14)-colors == 0
	var skip int = int(data[14])-40
	fmt.Printf("Colors start through: %d bytes\n", colors)
	fmt.Println("Availability of a palette:" , color_test)
	var height int = dec_to_dec(int(data[22]),int(data[23]),int(data[24]),int(data[25]))
	var witdh int = dec_to_dec(int(data[18]),int(data[19]),int(data[20]),int(data[21]))
	fmt.Printf("Сontour size: %d x %d\n", witdh, height)
	fmt.Printf("Colors bit: %d bit\n", bit)
	fmt.Printf("Skipped: %d byte\n", skip)

	var palette int = 0
	if skip !=0 {
		file.Seek(int64(skip-palette), 1)
		i = i+skip-palette
	}
	data = nil

	for ;true; {
		wri, err := file.Read(buf2)
		if err == io.EOF { // если конец файла
			break // выходим из цикла
		}
		data = append(data, buf2[:wri]...)
	}
	fmt.Println("Data will be write in (R)ed(G)reen(B)lue(A)lpha format")
	fmt.Print("Press Enter for continue\n")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
	var time1 int64 = time.Now().Unix()
	var completion int
	switch(bit) {
		case 32:
			completion = 0
		case 24:
			completion = witdh % 4
			fmt.Println("completion: ", completion)
			RGB_bit(completion,height,witdh,name,name_out, data...)
	}
	time1 = time.Now().Unix() - time1
	fmt.Printf("Time: %d h, %d m, %d s\n", time1/3600, (time1%3600)/60, time1%60)
	fmt.Print("END.\nPress Enter for close programm\n")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}
