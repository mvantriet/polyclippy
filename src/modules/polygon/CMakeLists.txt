set(LIB_TYPE OBJECT)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/edge)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/shape)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)

add_library (Polygon ${LIB_TYPE} Polygon.cpp)