#!/bin/bash
#
mpic++ -c -g communicator.cpp >& compiler.txt
if [ $? -ne 0 ]; then
  echo "Errors compiling communicator.cpp"
  exit
fi
#
mpic++ communicator.o -lm
if [ $? -ne 0 ]; then
  echo "Errors linking and loading communicator.o."
  exit
fi
#
rm communicator.o
#
mv a.out communicator
mpirun -np 4 communicator > communicator_local_output.txt
if [ $? -ne 0 ]; then
  echo "Errors running communicator"
  exit
fi
#
echo "Program output written to communicator_local_output.txt"
