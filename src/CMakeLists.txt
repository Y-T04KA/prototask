find_package(Protobuf CONFIG REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
file(GLOB PROTO_FILES *.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

add_executable(protobuf_parser main.cpp ${PROTO_SRCS} ${PROTO_HDRS} DelimetedMessagesStreamParser.hpp helpers.hpp)
IF(NOT WIN32)#так написано делать в доках CMake, но под MSVC не соберется
    target_link_libraries(protobuf_parser PRIVATE ${Protobuf_LIBRARIES})
endif()
if(WIN32)#а так соберется, потому что переменная выше под MSVC дает пути на длл к которым нельзя линковаться
    target_link_libraries(protobuf_parser PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
endif ()