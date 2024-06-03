set(SPICYC_GENERATED_SRC ${CMAKE_CURRENT_BINARY_DIR}/spicy_protobuf.cc
                         ${CMAKE_CURRENT_BINARY_DIR}/spicy___linker__.cc)
set(SPICYC_SRC_CMD ${SPICYC} -x ${CMAKE_CURRENT_BINARY_DIR}/spicy
                   ${PROJECT_SOURCE_DIR}/analyzer/protobuf.spicy)
add_custom_command(
  OUTPUT ${SPICYC_GENERATED_SRC}
  COMMAND ${SPICYC_SRC_CMD}
  COMMENT ${SPICYC_SRC_CMD}
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/analyzer/protobuf.spicy
  VERBATIM COMMAND_EXPAND_LISTS)

set(SPICYC_GENERATED_HDR ${CMAKE_CURRENT_BINARY_DIR}/spicy_protobuf.h)
set(SPICYC_HDR_CMD ${SPICYC} -P ${PROJECT_SOURCE_DIR}/analyzer/protobuf.spicy
                   -o ${SPICYC_GENERATED_HDR})
add_custom_command(
  OUTPUT ${SPICYC_GENERATED_HDR}
  COMMAND ${SPICYC_HDR_CMD}
  COMMENT ${SPICYC_HDR_CMD}
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/analyzer/protobuf.spicy
  VERBATIM COMMAND_EXPAND_LISTS)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(${CMAKE_PROJECT_NAME}_test protobuf.cpp ${SPICYC_GENERATED_SRC}
                                          ${SPICYC_GENERATED_HDR})
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE gtest_main spicy hilti)
target_include_directories(${CMAKE_PROJECT_NAME}_test
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)
