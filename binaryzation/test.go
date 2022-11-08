package main

import (
    "fmt"
    "os"
)

func main() {
    for {
		data := make([]byte, 8)
		n, err := os.Stdin.Read(data)
		if err == nil && n > 0 {
			fmt.Println("Hello", string(data))
		} else {
			break
		}
	}
}
