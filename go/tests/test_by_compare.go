package tests2

import(
  "context"
  "os/exec"
  "time"
  "fmt"
)

/* TODO:
4 threads:
generating input
recieving output from tester
recieving output from testee
validating
*/

/* OR:
2 threads
generating input
recieving output from tester && testee + validating on fly with CopyN and Compare
*/

func f(tester *exec.Cmd, testee *exec.Cmd, giveInput chan io.Writer) {
  var(
    testerBuf   *bytes.Buffer
    testeeBuf   *bytes.Buffer
    testerArr = make([]byte, 1024)
    testeeArr = make([]byte, 1024)
  )

  testerIn, err := tester.StdinPipe()
  testeeIn, err := testee.StdinPipe()
  testerOut, err := tester.StdoutPipe()
  testeeOut, err := testee.StdoutPipe()

  if err != nil {
    return nil
  }

  stdin := io.MultiWriter(testerIn, testeeIn)
  giveInput <- stdin

  for {
    a, err := io.ReadFull(testerOut, testerArr)
    b, err := io.ReadFull(testeeOut, testeeArr)

    switch(err) {
    case io.EOF:
      //do something
    case nil:
      //do nothing
    default:
      //??
    }

    if(flag && !bytes.Equal(testerArr, testeeArr)) {
      // error - wrong answer, send signals to other threads
      flag = false
    }
  }

  return
}

