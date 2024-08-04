cmake_minimum_required(VERSION 3.22)
project(C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tool)
include_directories(unit)
set(SOURCE unit/Decode.cpp
        unit/Decode.h
        tool/circularqueue.h
        tool/instruction.h
        unit/cpu.h
        unit/op_queue.cpp
        unit/reoderbuffer.cpp
        unit/reservation_stations.cpp
        unit/reservation_stations.h
        unit/reoderbuffer.h
        unit/registers.h
        unit/op_queue.h
        unit/memory.h
        unit/alu.h
        unit/loadstorebuffer.cpp
        unit/loadstorebuffer.h
        main.cpp
        unit/Predictor.h
#        intepreter.cpp
)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")

add_executable(
        CPU ${SOURCE})
