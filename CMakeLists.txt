project(CAmin)
cmake_minimum_required(VERSION 2.8)

set(CAMIN_VERSION_MAJOR 0)
set(CAMIN_VERSION_MINOR 1)
set(CAMIN_VERSION_PATCH 2)
set(CAMIN_VERSION_STRING ${CAMIN_VERSION_MAJOR}.${CAMIN_VERSION_MINOR}.${CAMIN_VERSION_PATCH})

add_definitions( -DEFL_BETA_API_SUPPORT=1 )
find_package(PkgConfig)
pkg_check_modules(LIBXML2 libxml-2.0)
pkg_check_modules(ECORE ecore-con ecore)
pkg_check_modules(EO eo)
pkg_check_modules(LIBURIPARSER liburiparser)
pkg_check_modules(LIBUV libuv)
configure_file( ${CMAKE_SOURCE_DIR}/libamin/include/config.h.in ${CMAKE_SOURCE_DIR}/libamin/include/config.h )
link_directories(
     ${LIBXML2_LIBRARY_DIRS} ${ECORE_LIBRARY_DIRS} ${EO_LIBRARY_DIRS} ${LIBURIPARSER_LIBRARY_DIRS}
)
include_directories(
     libamin/stage/ ${LIBXML2_INCLUDE_DIRS} ${ECORE_INCLUDE_DIRS} ${EO_INCLUDE_DIRS} ${LIBURIPARSER_INCLUDE_DIRS}
)
add_subdirectory(libamin)

add_executable(camin camin/camin.c)
add_executable(cainit cainit/cainit.c)
target_link_libraries(camin amin)
target_link_libraries(cainit amin ${LIBUV_LIBRARIES})

install(TARGETS camin DESTINATION bin)

