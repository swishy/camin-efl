set ( SRC_FILES "src/element.c" "src/xml_sax_base.c" "src/amin.c" "src/amin_elt.c" "src/amin_machine_spec.c" "src/amin_machine_spec_document.c" "src/amin_machine_spec_data.c")

add_library(amin SHARED ${SRC_FILES})
target_link_libraries(amin ${LIBXML2_LIBRARIES} ${EINA_LIBRARIES} ${ECORE_LIBRARIES} ${EO_LIBRARIES} ${LIBURIPARSER_LIBRARIES})
set_target_properties(amin PROPERTIES VERSION ${CAMIN_VERSION_STRING} SOVERSION ${CAMIN_VERSION_MAJOR})
install(TARGETS amin DESTINATION lib)
