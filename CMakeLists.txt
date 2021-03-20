project (polyclippy)
MESSAGE("<< Building " ${PROJECT_NAME} ">>")
cmake_minimum_required (VERSION 3.0)

MESSAGE("<<Building " ${CMAKE_BINARY_DIR} ">>")

# Set lib, archive and bin (executable) paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}/${CMAKE_SYSTEM_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}/${CMAKE_SYSTEM_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(CMAKE_BUILD_TYPE MATCHES debug)
    add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE MATCHES debug)

set(SRC_DIR src)
add_subdirectory (${SRC_DIR})

if(RUN_TESTS)
    MESSAGE("<< BUILDING AND RUNNING TESTS >>")
    enable_testing()
    add_subdirectory(test)
endif()