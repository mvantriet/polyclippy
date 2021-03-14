set(TEST_TARGET_NAME test_polyintersect)

add_executable (${TEST_TARGET_NAME} testPolyintersect.cpp)
target_link_libraries (${TEST_TARGET_NAME} polyclippy)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/edge)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/shape)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/polygon)

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME}
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET_NAME}>)