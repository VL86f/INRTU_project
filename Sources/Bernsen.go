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

func bernsen(sqrt, set_color, width, height int, color ...byte) []byte {
	var e_cof int = 15
	quest := make([][]int, height)
	for i := range quest {
		quest[i] = make([]int, width)
	}
	for y :=0;y<height;y++ {
		for x :=0;x<width;x++ {
			z := (x*3)+(y*width*3)+set_color
			quest[y][x] = int(color[z])
			//fmt.Print(" ", quest[y][x])
		}
		//fmt.Print("\n")
	}
	sqr := make([][]int, sqrt)
	for i := range sqr {
		sqr[i] = make([]int, sqrt)
	}
	var (
		step_w int = width/sqrt
		step_h int = height/sqrt
	)
	if width%sqrt != 0 {
		step_w++
	}
	if height%sqrt != 0 {
		step_h++
	}
	step := step_w*step_h
	ans := make([]byte, width*height)
	
	for k := 0;k<step;k++ {
		min := 255
		max := 0
		x :=0
		y :=0
		score_w := (k%step_w)*sqrt
		score_h := (int(k/step_w))*sqrt
		for y<sqrt { 
			ch := score_w+x
			ph := score_h+y
			if ch >= width || ph >= height {
				sw:= ch >= width
				if sw == true {
					sqr[y][x] = -1
				} else {
					sqr[y][x] = -2
				}
			} else {
				switch {
					case int(quest[ph][ch]) > max:
						max = int(quest[ph][ch])
					case int(quest[ph][ch]) < min:
						min = int(quest[ph][ch])
				}
				sqr[y][x] = int(quest[ph][ch])
			}
			x++
			if x>=sqrt {
				x=0
				y++
			}
		}
		/*fmt.Println("k: ", k)
		for y:=0;y<sqrt;y++ {
			for x:=0;x<sqrt;x++ {
			fmt.Print(" ", sqr[y][x])
			}
			fmt.Print("\n")
		}*/
		Avr := (min+max)/2 
		//fmt.Println("AVR: ", Avr)
		//s_min := 0
		//s_max := 0
		switch {
			case Avr < e_cof:
				//s_min = -1
				//s_max = -1
				for y:=0;y<sqrt;y++{
					for x:=0;x<sqrt;x++{
						sqr[y][x] = 0
					}
				}
			case Avr+e_cof>=255:
				//s_max = -1
				for y:=0;y<sqrt;y++{
					for x:=0;x<sqrt;x++{
						sqr[y][x] = 0
					}
				}
			case Avr+e_cof<=0:
				//s_min = -1
				for y:=0;y<sqrt;y++{
					for x:=0;x<sqrt;x++{
						sqr[y][x] = 255
					}
				}
			default:
				for y:=0;y<sqrt;y++{
					for x:=0;x<sqrt;x++{
						if sqr[y][x] >= Avr+e_cof {
							sqr[y][x] = 255
							//s_max++
						} else if sqr[y][x] >= 0 {
							sqr[y][x] = 0
							//s_min++
						}
					}
				}
		}
		for y:=0;y<sqrt;y++ {
			if sqr[y][x] < 0 {
				continue
			}
			for x:=0;x<sqrt;x++ {
				if sqr[y][x] < 0 {
					break
				}
				ch := ((k%step_w)*sqrt)+x
				ph := (int(k/step_w)*sqrt)+y
				if ch < width && ph < height {
				quest[ph][ch] = sqr[y][x]
				}
			}
		}
		for y:=0;y<height;y++ {
			for x:=0;x<width;x++ {
				z := x+(y*width)
				ans[z] = byte(quest[y][x])
			}
		}
	/*fmt.Printf("k%d min %d max %d Avr %d s_min %d s_max %d\n", k, min, max, Avr, s_min, s_max)
	for y:=0;y<sqrt;y++ {
			for x:=0;x<sqrt;x++ {
			fmt.Print(" ", sqr[y][x])
			}
			fmt.Print("\n")
		} */
		
	}
	return ans[:]
}

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
    //height++
    var width int = strings.Count(string(readed), ";")
    width = width/height
    fmt.Printf("Width %d Height %d \n", width, height)
	fmt.Println("Press enter to countinue")
    bufio.NewReader(os.Stdin).ReadBytes('\n')
    grey := make([]byte, 0)
    var (
        wi int = 0
    )
    var blok byte = 0
    for i := 0;i<len(readed);i++{
		cif := readed[i]
		switch(string(cif)) {
			case " ":
				grey = append(grey, blok)
				blok = 0
				wi++
			case ";":
				blok = 0
			case "\n":
				wi = 0
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
	
var sqrt int = 3

red := bernsen(sqrt, 0, width, height, grey...)
green := bernsen(sqrt, 1, width, height, grey...)
blue := bernsen(sqrt, 2, width, height, grey...)

/*green := bernsen(sqrt, 1, width, height, grey...)
blue := bernsen(sqrt, 2, width, height, grey...)
*/

	stri := strings.Split(name, ".")
	name_len := len(stri)
	var name_out string = "."+stri[name_len-1]
	name = strings.ReplaceAll(name, name_out, "-")
    name = name + "Bernsen.txt"
   file2, err := os.Create(name)
        if err != nil {
                fmt.Println("Out file is not created")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(2)
        }
    defer file2.Close() 
	
	for y:=0;y<height;y++ {
		for x:=0;x<width;x++ {
			z := x+(y*width)
			_, err1 := io.WriteString(file2, strconv.Itoa(int(red[z]))+" "+strconv.Itoa(int(green[z]))+" "+strconv.Itoa(int(blue[z]))+" 255;")
			if err1 != nil {
				panic(err1)
				os.Exit(1)
			}
		}

		_, err2 := io.WriteString(file2, "\n")
			if err2 != nil {
				panic(err2)
				os.Exit(1)
			}

	}
	
	
	time2 := time.Now().Unix() - time1
	fmt.Println("Done")
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Press enter to end the program")
    bufio.NewReader(os.Stdin).ReadBytes('\n')

}
