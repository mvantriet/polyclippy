set(TEST_TARGET_NAME test_util)

add_executable (${TEST_TARGET_NAME} testUtil.cpp)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME}
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET_NAME}>)