cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0016 NEW)
project(protobuf_parser VERSION 1.0.0 DESCRIPTION "Разбор потока length-prefiex Protobuf сообщений на С++")
set(CMAKE_CXX_STANDARD 20)
enable_testing()

include_directories(src)
add_subdirectory(test)
find_package(Protobuf CONFIG REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
file(GLOB PROTO_FILES src/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})


if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

MESSAGE(${Protobuf_LIBRARIES})
add_executable(protobuf_parser src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS} src/DelimetedMessagesStreamParser.hpp src/helpers.hpp)
IF(NOT WIN32)#так написано делать в доках CMake, но под MSVC не соберется
    target_link_libraries(protobuf_parser ${Protobuf_LIBRARIES})
endif()
if(WIN32)#а так соберется, потому что переменная выше под MSVC дает пути на длл к которым нельзя линковаться
    target_link_libraries(protobuf_parser PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
endif ()