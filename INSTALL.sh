#!/bin/bash

if [ ! -f "./Solver" ] 
then
    echo "file not exisit"
else 
    rm Solver
fi

mkdir -p build && cd build && cmake .. && make -f Makefile && cp Solver ..
