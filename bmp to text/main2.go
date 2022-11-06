// test project main.go начало кода на строке 101
package main

import ( // библиотеки
	"fmt"
	"io"
	"os"
	"bufio"
	"strconv"
	"math"
	"strings"
	"time"
)
func RGB_bit(completion,height,witdh int,name string,data ...byte) { // функция без возврата переменной (тип void)
	fmt.Println("24_bit Start")
	var comply int = completion * height // общее количество битов заполнения
	name = strings.ReplaceAll(name, ".bmp", ".txt") //смена имени файла
	file2 ,err1 := os.Create(name) // создание файла
	if err1 != nil { // если зайл не создался
		panic(err1)
		os.Exit(1)
	}	
	defer file2.Close() // в конце функции файл закрывается
	var max_size int = witdh * height // количество пикселей
	//fmt.Println("Completion: ", completion)
	if height > 0 { // если картинка записана стандартным, для bmp формата способом (слева направо, снизу вверх)
		witdh_out := 0 // ширина строки
		for x:=max_size;x>0;x-- { // пока не дойдёт до последнего пикселя
			if witdh_out == 0{ // если строка закончилась строка
				//fmt.Println("Enter: ", x)
				if x != max_size {
					//fmt.Println("Pressed: ", x)
					_,err := io.WriteString(file2, "\n") //запись символа в файл (_ мнимая переменная)
						if err != nil { // если запись не произошла
							panic(err)
							os.Exit(1)
						}
				}
				//fmt.Println("Skipped", completion)
				witdh_out = witdh
				comply = comply - completion // смещение пикселей в текущей строке
				}
			y := (x*3) + comply 
			z := strconv.Itoa(int(data[y-1])) + " "+ strconv.Itoa(int(data[y-2])) + " " +strconv.Itoa(int(data[y-3])) + " 255;" // создание информации о пиксели
			_,err := io.WriteString(file2, z) //запись информации о пикселе 
			if err != nil {
				panic(err)
				os.Exit(1)
			}	
			witdh_out-- // изменение ширины строки 
		}	
			//fmt.Println("ALL: ", all)
	}	
}	
func dec_to_dec(data ...int) (int) { // функция с возвратом integer переменной
	var ran int = len(data) // размер массива
	var ans int = 0
	var hex string = "0123456789ABCDEF" // массив шестнадцатеричных чисел
	var part string 
	var chisl string = ""
	for i:=ran-1;i>=0;i-- { // перевод массива десятичных чисел типа integer в шестнадцатеричное число в записи типа string
		part = ""
		if data[i] == 0 {
			part = "00"
		}	
		for pr:=data[i];pr>0; {
			x := pr % 16 
			part = string(hex[x]) + part
			pr = pr / 16 // % - взятие остатка деления ; / - деление - если делится целое число (integer) то в ответе записывается только целая часть результата деления
		}
		chisl = chisl + part
	}
//	fmt.Println("Chisl?", chisl) 
	ran = len(chisl)
	for i:=0;i<ran;i++ { // перевод шестнадцатеричного числа в записи типа string в десятичное число типа integer
		x := 0
		switch(string(chisl[i])) {
			case "A": x = 10
			case "B": x = 11
			case "C": x = 12
			case "D": x = 13
			case "E": x = 14
			case "F": x = 15
			default: 
				z, err := strconv.Atoi(string(chisl[i])) // перевод из string в integer
				if err != nil { // если в string переменной оказались не числовые символы
					panic(err)
					bufio.NewReader(os.Stdin).ReadBytes('\n')
					os.Exit(5)
				}
				x = z
				
		}
		y := x * int(math.Pow(16, float64(ran-i-1))) // math.Pow(int, float64) - возведение в степень
		ans = ans+y
	}	
	return ans // возврат полученного числа
}


func main() {

	var name string
	fmt.Println("Name?")
	fmt.Scanln(&name) //ввод имени файла
	fmt.Println("Attention. This is test programm")
//	file2 ,err1 := os.Create("exit.txt")
//	if err1 != nil {
//		fmt.Println(err1)
//		os.Exit(1)
//	}	
//	defer file2.Close()
	file, err := os.Open(name) //открытие файла
	if err != nil { //действие, если файл не откроется
		panic(err)
		os.Exit(1) //предварительное завершение программы
	}
	defer file.Close() // .Close() закрытие файла; defer выполнение команды в конце работы
	
	data := make([]byte, 0)
	buf := make([]byte, 54) //создание массивов с заранее неизвестным размером (срезов) типа byte (unsigned shortint)
	buf2 := make([]byte, 1024)
	var i int
	
	
		wri, err := file.Read(buf) // чтение первых 54 байт
		if err == io.EOF { // если конец файла 
			fmt.Println("File is end")
		}
		
	//	fmt.Print(data[:wri])
		data = append(data, buf[:wri]...) // добавление новых элементов в срез
	
	if len(data) < 53 {
		fmt.Println("Error.Invalid file type or file have very small size") //проверка принятых данных на размер
		bufio.NewReader(os.Stdin).ReadBytes('\n') //считывание нажатие Enterа
		os.Exit(3)
	}	
	if data[0] != 66 && data[1] != 77 && data[15] != 0 && data[16] != 0 { // проверка типа файла
		fmt.Println("Error. Invalid file type")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}else if data[14] != 40 && data[14] != 108 && data[14] != 124 { //проверка версии файла (версии расширения .bmp)
		fmt.Println("Error. Unsupported file version") 
		fmt.Print("Header Version: ")
		fmt.Println(data[14])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}
	fmt.Println("Type of file: passed")
	if data[26] != 1 && data[27] != 0 && data[29] != 0  { // проверка данных глубины цвета (1 цветовая плоскость и глубина цвета не превышает 255 бит 
		fmt.Println("Error. Unsupported file version")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	} else if data[28] == 16 || data[28] >= 32 { // если глубина цвета больше 32 бит или равна 16 бит
		fmt.Println("Error. Unsupported color depth")
		fmt.Print("Color depth: ")
		fmt.Println(data[28])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	} else if data[28] <= 8 { // если глубина цвета меньше или равна 8 бит
		fmt.Println("Sorry. But this color depth is not supported yet.")
		fmt.Print("Color depth: ")
		fmt.Println(data[28])
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
		
	} else if data[30] != 0 && data[31] != 0 && data[32] !=0 && data[33] !=0 { // проверка данных на зашированность и сжатие
		fmt.Println("Error. Data is compressed or encrypted")
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		os.Exit(2)
	}
	fmt.Println("Support test: passed")
	var bit int = int(data[28])
	var size int = dec_to_dec(int(data[2]),int(data[3]),int(data[4]),int(data[5])) //получение целых, числовых значений
	fmt.Printf("File of size: %d bytes\n", size)
	var colors int = dec_to_dec(int(data[10]),int(data[11]),int(data[12]),int(data[13]))
	var color_test bool = (size-int(data[14])-14)-colors == 0 // проверка на наличие в файле палитры цветов
	var skip int = int(data[14])-40 //размер оставшейся шапки
	fmt.Printf("Colors start through: %d bytes\n", colors)
	fmt.Println("Availability of a palette:" , color_test)
	var height int = dec_to_dec(int(data[22]),int(data[23]),int(data[24]),int(data[25]))
	var witdh int = dec_to_dec(int(data[18]),int(data[19]),int(data[20]),int(data[21]))
	fmt.Printf("Сontour size: %d x %d\n", witdh, height)
	fmt.Printf("Colors bit: %d bit\n", bit)
	fmt.Printf("Skipped: %d byte\n", skip)
	var palette int = 0
	if skip !=0 {
		file.Seek(int64(skip-palette), 1) // пропустить оставшуюся часть шапки
		i = i+skip-palette
	}
	data = nil // очистка файла
	
	for ;true; { // чтение файла
		wri, err := file.Read(buf2)
		if err == io.EOF { // если конец файла
			break // выходим из цикла
		}
		data = append(data, buf2[:wri]...)
		
	}
	//fmt.Println(len(data))
	fmt.Println("Data will be write in (R)ed(G)reen(B)lue(A)lpha format")
	fmt.Print("Press Enter for continue\n")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
	var time1 int64 = time.Now().Unix() // текущее время в секундах для таймера
	var completion int // биты заполнения
	switch(bit) {
		case 32:
			completion = 0
		case 24:
			completion = 3 * witdh % 4 // вычисление количества бит заполнения 
			fmt.Println("completion: ", completion) 
			RGB_bit(completion,height,witdh,name, data...) //извлечение и запись данных
	}	
	time1 = time.Now().Unix() - time1
	fmt.Printf("Time: %d h, %d m, %d s\n", time1/3600, (time1%3600)/60, time1%60)
	fmt.Print("END. Press Enter for close programm\n")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}
