#!/bin/bash

lport=8888

outhost="$1"
outport="$2"

infile='proxy-in'
outfile='proxy-out'

mkfifo backpipe
nc -l -p $lport 0<backpipe | tee $infile | nc $outhost $outport | tee $outfile 1>backpipe
