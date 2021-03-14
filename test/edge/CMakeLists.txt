set(TEST_TARGET_NAME test_edge)

add_executable (${TEST_TARGET_NAME} testEdge.cpp)
target_link_libraries (${TEST_TARGET_NAME} polyclippy)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/edge)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME}
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET_NAME}>)