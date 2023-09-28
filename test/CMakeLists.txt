project(gtests)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)


find_package(GTest CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)


if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(testDMSP Test_DelimetedMessagesStreamParser.cpp ${CMAKE_SOURCE_DIR}/src/helpers.hpp ${CMAKE_BINARY_DIR}/src/work.pb.h ${CMAKE_BINARY_DIR}/src/work.pb.cc)
target_link_libraries(testDMSP PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
add_executable(testHelpers Test_helpers.cpp ${CMAKE_SOURCE_DIR}/src/helpers.hpp ${CMAKE_BINARY_DIR}/src/work.pb.h ${CMAKE_BINARY_DIR}/src/work.pb.cc)
target_link_libraries(testHelpers PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_test(prototestDMSP testDMSP)
add_test(prototestHelpers testHelpers)

