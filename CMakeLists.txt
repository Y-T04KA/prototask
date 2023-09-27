cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0016 NEW)
project(protobuf_parser
        VERSION 1.0.0
        DESCRIPTION "Разбор потока length-prefiex Protobuf сообщений на С++"
        LANGUAGES CXX)#i saw it's good to define lang here
set(CMAKE_CXX_STANDARD 20)
enable_testing()#must be in root .txt
add_subdirectory(src)
#include_directories(src) - another way for dirs without CMakeLists.txt, was in template, but generally unrecommended to use
add_subdirectory(test)
#message(классический дебаг принтом)


