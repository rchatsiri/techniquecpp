#!/bin/bash
#
mpic++ -c -g processor_hello.cpp >& compiler.txt
if [ $? -ne 0 ]; then
  echo "Errors compiling communicator.cpp"
  exit
fi
#
mpic++ processor_hello.o -lm
if [ $? -ne 0 ]; then
  echo "Errors linking and loading communicator.o."
  exit
fi
#
rm processor_hello.o
#
mv a.out processor_hello
mpirun -np 4 processor_hello > processor_hello_output.txt
if [ $? -ne 0 ]; then
  echo "Errors running communicator"
  exit
fi
#
echo "Program output written to communicator_local_output.txt"
