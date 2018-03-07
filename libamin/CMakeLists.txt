# set ( SRC_FILES "stage/amin.c" "stage/amin_elt.c" "stage/xml_sax_base.c" "stage/amin_machine_spec.c" "stage/amin_machine_spec_document.c" "stage/amin_machine_spec_data.c")
set ( SRC_FILES "stage/amin.c")

add_library(amin SHARED ${SRC_FILES})
target_link_libraries(amin ${LIBXML2_LIBRARIES} ${ECORE_LIBRARIES} ${EO_LIBRARIES} ${LIBURIPARSER_LIBRARIES})
set_target_properties(amin PROPERTIES VERSION ${CAMIN_VERSION_STRING} SOVERSION ${CAMIN_VERSION_MAJOR})
install(TARGETS amin DESTINATION lib)
