#!/bin/bash
#
make  >& compiler.txt
if [ $? -ne 0 ]; then
  echo "Errors compiling source"
  exit
fi
./scanner >& result.txt 
if [ $? -ne 0 ]; then
  echo "Error from result"
  exit
fi
