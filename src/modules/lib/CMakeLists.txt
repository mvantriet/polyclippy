set(LIB_TYPE SHARED)

include_directories (${CMAKE_SOURCE_DIR}/src/modules/edge)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/point)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/util)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/shape)
include_directories (${CMAKE_SOURCE_DIR}/src/modules/polygon)

add_library(polyclippy SHARED $<TARGET_OBJECTS:Polygon>
                                $<TARGET_OBJECTS:Edge>
                                $<TARGET_OBJECTS:Shape>)

string(CONCAT EXPORT_HEADERS
        "${CMAKE_SOURCE_DIR}/src/modules/polygon/Polygon.h;"
        "${CMAKE_SOURCE_DIR}/src/modules/edge/Edge.h;"
        "${CMAKE_SOURCE_DIR}/src/modules/point/Point.h;"
        "${CMAKE_SOURCE_DIR}/src/modules/shape/Shape.h;"
        )

MESSAGE("<< ${EXPORT_HEADERS} >>")

set_target_properties(polyclippy PROPERTIES PUBLIC_HEADER 
    "${EXPORT_HEADERS}")

INSTALL(TARGETS polyclippy 
        LIBRARY DESTINATION lib/
        PUBLIC_HEADER DESTINATION include/polyclippy
)