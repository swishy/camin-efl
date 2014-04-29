add_subdirectory(machine)
file(GLOB_RECURSE SRC_FILES *.c)
add_library(amin SHARED ${SRC_FILES})
set_target_properties(amin PROPERTIES VERSION ${CAMIN_VERSION_STRING} SOVERSION ${CAMIN_VERSION_MAJOR})

