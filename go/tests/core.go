package tests

import (
	"context"
	"os/exec"
	"time"
        "fmt"
)

type JudgeFunc func(uint, *exec.Cmd)(float64, error)

type RunConfig struct {
  Judge     JudgeFunc
  Timeout   time.Duration
  Name      string
  Args      []string
}

type BenchInfo struct {
  Seconds   float64
  Error     error
}

func RunThread(runconf RunConfig, numOfTests uint, send chan BenchInfo, threadnum uint) (error) {
  for i:=uint(1); i<numOfTests; i++ {
    ctx, cancel := context.WithTimeout(context.Background(), runconf.Timeout)
    cmd := exec.CommandContext(ctx, runconf.Name, runconf.Args...)

    seconds, err := runconf.Judge(i, cmd)
    cancel()
    send <- BenchInfo{seconds, err}

    if err != nil {
      return err
    }
  }

  send <- BenchInfo{-float64(threadnum), nil}
  return nil
}

func Run(cfg RunConfig, threads uint) error{
  var(
    average float64
    i       uint
  )

  rec := make(chan BenchInfo, threads)
  for i:=uint(1); i<=threads; i++ {
    go RunThread(cfg, 5, rec, i)
  }

  for binfo := range(rec) {
    if binfo.Error != nil {
      /* TODO: close program more gently :) */
      close(rec)
      return binfo.Error
    }

    if binfo.Seconds < 0 {
      fmt.Printf("Thread %.0f finished.\n", -binfo.Seconds)
      threads--
    } else {
      i++
      average += (binfo.Seconds - average) / float64(i)
      fmt.Printf("Time: %fs - Average: %fs\n", binfo.Seconds, average)
    }

    if threads == 0 {
      close(rec)
    }
  }

  return nil
}

