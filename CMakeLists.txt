cmake_minimum_required(VERSION 3.24)
project(prototask)
set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf CONFIG REQUIRED)
find_package(Boost)

IF(APPLE)


endif()

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(prototask main.cpp protobuf/work.pb.cc protobuf/work.pb.h DelimetedMessagesStreamParser.cpp DelimetedMessagesStreamParser.h serialize.cpp parseDelimited.cpp)
add_executable(write-test write-test.cpp protobuf/work.pb.cc protobuf/work.pb.h)
add_executable(read-test read-test.cpp protobuf/work.pb.h protobuf/work.pb.cc)
target_link_libraries(prototask PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(write-test PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(read-test PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)