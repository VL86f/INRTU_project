package main

import(
 "fmt"
 "os"
 "io"
 "bufio"
 "strconv"
 "time"
 "math"
 "strings"
)

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
    var height int = strings.Count(string(readed), "\n")
    //height++
    var width int = strings.Count(string(readed), ";")
    width = width/height
    rgb := make([]byte, 0)
    var blok byte = 0
    fmt.Println("1")
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
    fmt.Println("2")
	ans := make([]byte, 0)
	for x := 0;x<(len(rgb)/3);x++ {
        a := rgb[x*3]
        b := rgb[x*3+1]
        c := rgb[x*3+2]
        y := math.Ceil(((float64(a)*0.2126)+(float64(b)*0.7152)+(float64(c)*0.0722))+0.5)
        ans = append(ans, byte(y))
    }

    //var ans_out string = ""
    var tr int = width
    stri := strings.Split(name, ".")
	k := len(stri)
	var name_out string = "."+stri[k-1]
	name = strings.ReplaceAll(name, name_out, "-")
    name = name + "Grey.txt"
   file2, err := os.Create(name)
        if err != nil {
                fmt.Println("Out file is not created")
                fmt.Println("Press enter to end the program")
                bufio.NewReader(os.Stdin).ReadBytes('\n')
                os.Exit(2)
        }
    defer file2.Close()

    for x := 0;x<int(len(rgb)/3);x++ {
        if tr==0 {
            _, er2 := io.WriteString(file2, "\n")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}
            tr = width
        }
        _,er := io.WriteString(file2, strconv.Itoa(int(ans[x])) + " " + strconv.Itoa(int(ans[x])) + " " + strconv.Itoa(int(ans[x])) + " 255;")
	if er != nil {
				panic(er)
				os.Exit(1)
			}

        tr--
    }
    fmt.Println("3")
_, er2 := io.WriteString(file2, "\n")
			if er2 != nil {
				panic(er2)
				os.Exit(1)
			}

 /*   _, err1 := io.WriteString(file2, ans_out)
			if err != nil {
				panic(err1)
				os.Exit(1)
			}
*/
	time2 := time.Now().Unix() - time1
	fmt.Println("Done")
    fmt.Printf("Time: %d h, %d m, %d s\n", time2/3600, (time2%3600)/60, time2%60)
    fmt.Println("Press enter to end the program")
    bufio.NewReader(os.Stdin).ReadBytes('\n')
}
