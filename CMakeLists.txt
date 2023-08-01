cmake_minimum_required(VERSION 3.24)
project(prototask)
set(CMAKE_CXX_STANDARD 20)

find_package(protobuf CONFIG REQUIRED)


IF(APPLE)


endif()

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(prototask main.cpp protobuf/work.pb.cc protobuf/work.pb.h)
target_link_libraries(prototask PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)