cmake_minimum_required(VERSION 3.24)
project(prototask)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

FETCHCONTENT_DECLARE(
        GTest
        URL https://github.com/google/googletest/archive/06f44bc951046150f1348598854b211afdcf37fc.zip
        FIND_PACKAGE_ARGS NAMES GTest
)

FETCHCONTENT_DECLARE(
        Protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG v23.2
        SOURCE_SUBDIR cmake
        FIND_PACKAGE_ARGS NAMES GTest googletest
)

IF(APPLE)


endif()

if(WIN32)
    set(CMAKE_C_COMPILER "msvc")
    set(CMAKE_CXX_COMPILER "msvc")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FETCHCONTENT_MAKEAVAILABLE(Protobuf GTest)

add_executable(prototask main.cpp)
