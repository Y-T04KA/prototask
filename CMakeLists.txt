cmake_minimum_required(VERSION 3.24)
project(prototask)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)



FETCHCONTENT_DECLARE(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG v23.2
        FIND_PACKAGE_ARGS NAMES GTest
)

IF(APPLE)


endif()

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FETCHCONTENT_MAKEAVAILABLE(protobuf)

add_executable(prototask main.cpp)
