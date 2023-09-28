cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0016 NEW)
project(protobuf_parser
        VERSION 1.0.0
        DESCRIPTION "Разбор потока length-prefiex Protobuf сообщений на С++"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include(CTest)
add_subdirectory(src)
add_subdirectory(test)

