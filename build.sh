#!/bin/bash

STR_DBG="debug"

if [ $# -eq 1 ] && [ $1 = $STR_DBG ]
then
    set -x
    g++ -std=c++11 src/main.cpp src/CPUData.cpp src/CPUSnapshot.cpp src/CPUStatsPrinter.cpp src/OptionsParser.cpp -o cpu-stat-DBG -O0 -g -Wall
else
    set -x
    g++ -std=c++11 src/main.cpp src/CPUData.cpp src/CPUSnapshot.cpp src/CPUStatsPrinter.cpp src/OptionsParser.cpp  -o cpu-stat -O3 -s -Wall
fi
