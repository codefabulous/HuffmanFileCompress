cmake_minimum_required(VERSION 3.5)
project(HuffmanCompressCPro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Huffman.cpp Huffman.h Compress.cpp Compress.h File.cpp File.h)
add_executable(HuffmanCompressCPro ${SOURCE_FILES})