package main

import(
  "fmt"
  "bytes"
  "os"
  "io"
)

func main() {
  buf := bytes.NewBuffer(nil)
  sbuf := make([]byte, 8)

  n, err := io.ReadFull(os.Stdin, sbuf)
  buf.Write(sbuf)
  n, err = io.ReadFull(os.Stdin, sbuf)
  buf.Write(sbuf)

  fmt.Println(buf.Len(), n, err)
  os.Stdout.Write(sbuf)

  return
}

