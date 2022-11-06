package main

import(
 "fmt"
 "os"
 "io"
 "bufio"
 "strconv"
 "time"
 "strings"
)

func two_graph(c chan string, color_1 ,color_2 int,data  ...byte)  {
    var le int = len(data)/3
    var mn int = 256/8
    ans := make([][]int, mn)
    for i := range ans {
        ans[i] = make([]int, mn)
    }
    var opr int = 0
    for x := 0;x<le;x++ {
        i := x*3+color_1
        kl := data[i]
        for y :=0;<le;y++ {
            j := x*3+color_2
            k2 := data[j]
            for q := 0;q<mn;q++ {
                min_v := 0+4*opr
                min_h := 0+4*q
                max_v := 0+4*(opr+1)
                max_h := 0+4(q+1)

            }
        }
        opr++
    }

}


func one_graph(c chan string,color int,data   ...byte)  {
    var le int = len(data)/3
    var mn int = 256/8
    ans := make([]int, mn)
    var ans_out string =""
    var y byte = 0
    for x := 0;x<le;x++ {
            i := x*3+color
            y = data[i]
            for k := 0;k<mn;k++ {
                    min := 0 + 4*k
                    max := 0 + 4*(k+1)
                    if min<=int(y) && int(y)<max {
                        ans[k]++
                        break
                    }

            }
    }
    for x := 0;x<mn;x++ {
        ans_out = ans_out + strconv.Itoa(ans[x]) + ";"
    }
    c <- ans_out
}

func main() {
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
	tm := time.Now().Unix()
	time2 := time.Now().Unix() - time1
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Data is being processed")
    var (
        r chan string = make(chan string)
        g chan string = make(chan string)
        b chan string = make(chan string)
        //rb chan string = make(chan string)
        //rg chan string = make(chan string)
        //bg chan string = make(chan string)
    )
    go one_graph(r, 0, rgb...)
    go one_graph(g, 1, rgb...)
    go one_graph(b, 2, rgb...)

    red := <- r
    green := <- g
    blue := <- b
   // redgreen := <- rg
    // redblue := <- rb
    // greenblue := <- bg
    time2 = time.Now().Unix() - tm
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Writing")
    stri := strings.Split(name, ".")
	k := len(stri)
	var name_out string = "."+stri[k-1]
	name = strings.ReplaceAll(name, name_out, "-")
    name = name + "Analyz.csv"
   file2, err := os.Create(name)
        if err != nil {
                fmt.Println("Out file is not created")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(2)
        }
    defer file2.Close()
    var header string = "Graphic step = 4\n"
    var fileout string = header + "\n" + "RED:;" + red + "\nGREEN:;" + green + "\nBLUE:;" + blue
    _, err1 := io.WriteString(file2, fileout)
			if err != nil {
				panic(err1)
				os.Exit(1)
			}
    fmt.Println("Done")
    time1 = time.Now().Unix() - time1
	fmt.Printf("Time: %d h, %d m, %d s\n", time1/3600, (time1%3600)/60, time1%60)
    fmt.Println("Press enter to end the program")
    bufio.NewReader(os.Stdin).ReadBytes('\n')
}
