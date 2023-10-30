cmake_minimum_required(VERSION 3.5.1)

project(cpu-stat LANGUAGES CXX VERSION 0.01.03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# main executable
add_executable(
    cpu-stat
    src/main.cpp
    src/CPUData.h
    src/CPUSnapshot.h
    src/CPUStatsPrinter.h
    src/OptionsParser.h
    src/CPUData.cpp
    src/CPUSnapshot.cpp
    src/CPUStatsPrinter.cpp
    src/OptionsParser.cpp
)

target_include_directories(
    cpu-stat
    PRIVATE src/
)

# installation
include(GNUInstallDirs)
install(TARGETS cpu-stat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
