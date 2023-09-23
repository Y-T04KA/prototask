cmake_minimum_required(VERSION 3.24)
project(prototask)
set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf CONFIG REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
file(GLOB PROTO_FILES *.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

IF(APPLE)


endif()

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

endif()


add_executable(prototask main.cpp ${PROTO_SRCS} ${PROTO_HDRS} DelimetedMessagesStreamParser.cpp DelimetedMessagesStreamParser.h serialize.cpp)
target_link_libraries(prototask ${Protobuf_LIBRARIES})