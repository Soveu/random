package main

import(
  "fmt"
  "os/exec"
  "io"
  "bytes"
  "errors"
  "time"
  "./tests"
)

func judge(_ uint, cmd *exec.Cmd) (float64, error) {
  stdin, err := cmd.StdinPipe()

  if err != nil {
    return -1, err
  }

  input := "import time; time.sleep(0.5); print('123')"
  io.WriteString(stdin, input)
  stdin.Close()

  expected := []byte("123\n")

  timePoint := time.Now()
  out, err := cmd.Output()
  deltaTime := time.Since(timePoint)

  if err != nil {
    return -2, err
  }

  if !bytes.Equal(out, expected) {
    return -3, errors.New(fmt.Sprintf("Got:\n%s\nExpected:\n%s\nInput:\n%s\n",
                                  string(out), string(expected), input))
  }

  return deltaTime.Seconds(), nil
}

func main() {
  cfg := tests.RunConfig{
    Judge:    judge,
    Timeout:  time.Second*5,
    Name:     "python",
    Args:     []string{},
  }

  if err := tests.Run(cfg, 4); err != nil {
    fmt.Println(err)
  }
}

