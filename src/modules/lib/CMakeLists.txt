set(LIB_TYPE SHARED)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/edge)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/shape)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/polygon)

add_library(polyclippy SHARED $<TARGET_OBJECTS:Polygon>
                                $<TARGET_OBJECTS:Edge>
                                $<TARGET_OBJECTS:Shape>)