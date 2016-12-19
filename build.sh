set -x
g++ -std=c++11 src/main.cpp src/CPUData.cpp src/CPUSnapshot.cpp -o cpu-stat-DBG -O0 -g -Wall
g++ -std=c++11 src/main.cpp src/CPUData.cpp src/CPUSnapshot.cpp -o cpu-stat -O3 -s -Wall
