package main

import (
    "fmt"
    "os"
	"strings"
	"time"
	"io"
	"strconv"
	"bufio"
)

func main() {
	/*stream := make([]byte, 256)
	name_file := make([]byte, 0)
    for {
		n, err := os.Stdin.Read(stream)
		if err == nil {
			if n == 0 {
				continue
			} else {
				name_file = append(name_file, stream[:n]...)
				break
			}
		} else {
			os.Exit(1)
		}
	}
	fmt.Println("Attention!! This programm work with Grey palette")

	var name string = string(name_file)
	fmt.Println(string(name_file))
	fmt.Println("Name:",name)*/
	var name string
    fmt.Println("Enter File name:")
    fmt.Scanln(&name)
	file, err := os.Open(name)
        if err != nil {
                fmt.Println("File is not finded")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(1)
        }
    defer file.Close()
    time1 := time.Now().Unix()
    fmt.Println("File is opening")
    read := make([]byte, 1024)
    readed := make([]byte, 0)
    for {
        wri, err := file.Read(read)
            if err == io.EOF {
                break
            }
        readed = append(readed, read[:wri]...)
    }

	var height int = strings.Count(string(readed), "\n")
    var width int = strings.Count(string(readed), ";")
    width = width/height
    rgb := make([]byte, 0)
    var blok byte = 0
    for i := 0;i<len(readed);i++{
		cif := readed[i]
		switch(string(cif)) {
			case " ":
				rgb = append(rgb, blok)
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


	 stri := strings.Split(name, ".")
	k := len(stri)
	var name_out string = "."+stri[k-1]
	name = strings.ReplaceAll(name, name_out, "-")
    name = name + "Black.txt"
   file2, err := os.Create(name)
        if err != nil {
                fmt.Println("Out file is not created")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(2)
        }
    defer file2.Close()

	//var ans string = ""
	var tr int = width*3
	fmt.Println(len(rgb))
	for x :=0; x<(len(rgb));x++ {
		if tr==0 {
            _, er2 := io.WriteString(file2, "\n")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}
            tr = width * 3
        }
		if rgb[x] < 128 {
			_, er2 := io.WriteString(file2, "0 ")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}
		} else {
			_, er2 := io.WriteString(file2, "255 ")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}
		}
		if x%3==2 {
			_, er2 := io.WriteString(file2, "255;")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}
		}
		tr--

	}



	time2 := time.Now().Unix() - time1
	fmt.Println("Done")
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Press enter to end the program")
    bufio.NewReader(os.Stdin).ReadBytes('\n')

}
