cmake_minimum_required (VERSION 3.5.1)
project (Multicast_Totally_Ordered)
include_directories(include)

file (GLOB SOURCES "src/*.cpp")

add_executable (multicast ${SOURCES})