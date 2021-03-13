set(LIB_TYPE OBJECT)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)

add_library (Edge ${LIB_TYPE} Edge.cpp)