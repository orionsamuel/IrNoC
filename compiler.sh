#!/bin/bash

export SYSTEMC_HOME=/home/samuel/systemc

g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o main main.cpp -lsystemc -lm
