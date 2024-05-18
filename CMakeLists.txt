cmake_minimum_required(VERSION 3.5.1)

project(cpu-stat LANGUAGES CXX VERSION 0.01.03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# main executable
add_executable(
    cpu-stat
    src/main.cpp
    src/CPUStat.h
    src/CPUData.h
    src/CPUSnapshot.h
    src/CPUStatsPrinter.h
    src/OptionsParser.h
    src/CPUData.cpp
    src/CPUSnapshot.cpp
    src/CPUStatsPrinter.cpp
    src/OptionsParser.cpp
)



ADD_LIBRARY( 
    cpu-stat-lib STATIC
    #src/main.cpp
    src/CPUStat.h
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

target_include_directories(
    cpu-stat-lib
    PUBLIC src/
)

# Add the -fPIC flag to the compilation options for your_library_name
set_target_properties(cpu-stat-lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# installation
include(GNUInstallDirs)
install(TARGETS cpu-stat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install the library
install(TARGETS cpu-stat-lib
    EXPORT cpu-stat-lib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
