add_subdirectory(machine)
file(GLOB_RECURSE SRC_FILES *.c)
add_library(amin SHARED ${SRC_FILES})
target_link_libraries(amin ${LIBXML2_LIBRARIES} ${ECORE_LIBRARIES} ${EO_LIBRARIES} ${LIBURIPARSER_LIBRARIES})
set_target_properties(amin PROPERTIES VERSION ${CAMIN_VERSION_STRING} SOVERSION ${CAMIN_VERSION_MAJOR})
install(TARGETS amin DESTINATION lib)

