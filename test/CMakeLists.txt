project(gtests)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)#так, наверное очень плохо, но я пока не придумал другого пути чтобы делать протобаф сообщения в
find_package(GTest CONFIG REQUIRED)

add_executable(testDMSP Test_DelimetedMessagesStreamParser.cpp)
target_link_libraries(testDMSP PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_executable(testHelpers Test_helpers.cpp)
target_link_libraries(testHelpers PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(prototest testDMSP testHelpers)


