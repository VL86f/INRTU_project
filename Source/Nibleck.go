package main

import (
	"math"
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
    height++
    var width int = strings.Count(string(readed), ";")
    width = width/height
    fmt.Printf("Width %d Height %d \n", width, height)
	fmt.Println("Press enter to countinue")
    bufio.NewReader(os.Stdin).ReadBytes('\n')
    grey := make([][]byte, height*3)
	for i := range grey {
        grey[i] = make([]byte, width*3)
    }
    var (
        he int = 0
        wi int = 0
    )
    var blok byte = 0
    for i := 0;i<len(readed);i++{
		cif := readed[i]
		switch(string(cif)) {
			case " ":
				grey[he][wi] = blok
				blok = 0
				wi++
			case ";":
				blok = 0
			case "\n":
				he++
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
	var ans_out string = ""
	var step int = 25 // сторона квадрата вводите только нечётные числа
	var k float32 = -0.2
	ocr := make([][]float64, step)
	for i := range ocr {
        ocr[i] = make([]float64, step)
    }
	a := step/2
	var sum float64
	for x := 0;x<height;x++ {
		for y :=0;y<width;y++ {
			sum = 0
			cent := 0
			for z1 := 0;z1<step;z1++ {
				//fmt.Println("1 ", x-z1+a)

					//fmt.Println("Step X")
					for z2 := 0;z2<step;z2++ {
						if y-z2+a<0 || x-z1+a<0 || y-z2+a>=width || x-z1+a>=height {
							ocr[step-z1-1][step-z2-1] = -1
						} else {
							//fmt.Printf("X: %d  Y: %d\n", x, y)
							//fmt.Printf("Z1: %d  Z2: %d\n", z1, z2)
							ocr[step-z1-1][step-z2-1] = float64(grey[(x-z1+a)*3][(y-z2+a)*3])/255
							cent++
						}
					}

			}
		sum = 0
		//fmt.Println("sum ", sum)
		for c :=0;c<step;c++ {
			for d :=0;d<step;d++ {
				if ocr[c][d] != -1 {
					sum = sum + ocr[c][d]
				}
				//fmt.Println("sum ", sum)
				//fmt.Print(" ", ocr[c][d])
			}
			//fmt.Printf("\n")
		}
		sr := sum/float64(cent)
		co := 0.0
		for c :=0;c<step;c++ {
			for d :=0;d<step;d++ {
				if ocr[c][d] != -1 {
					co = co + (ocr[c][d]-sr)
				}
			}
		}
		sco1 := co/float64(cent)
		sco2 := (co*co)/float64(cent)
		sco2 = math.Pow(sco2,0.5)
		pr := float32(sco1)+k*float32(sco2)
		sg := grey[x][y]/255
		if sg<= byte(pr) {
			ans_out = ans_out + "0 0 0 255;"
		} else {
			ans_out = ans_out + "255 255 255 255;"
		}
		/*fmt.Println("pr ", pr)
		fmt.Println("sco2 ", sco2)
		fmt.Println("sco1 ", sco1)
		fmt.Println("sum ", sum)
		fmt.Println("pr ", sr)
		fmt.Println("C ", cent) */
		}
		if x<height-1 {
			ans_out = ans_out +"\n"
		}

	}




	stri := strings.Split(name, ".")
	name_len := len(stri)
	var name_out string = "."+stri[name_len-1]
	name = strings.ReplaceAll(name, name_out, "-")
    name = name + "Nibleck.txt"
   file2, err := os.Create(name)
        if err != nil {
                fmt.Println("Out file is not created")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(2)
        }
    defer file2.Close()

	 _, err1 := io.WriteString(file2, ans_out)
			if err != nil {
				panic(err1)
				os.Exit(1)
			}

	time2 := time.Now().Unix() - time1
	fmt.Println("Done")
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Press enter to end the program")
    bufio.NewReader(os.Stdin).ReadBytes('\n')

}
