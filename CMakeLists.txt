project(CAmin)
cmake_minimum_required(VERSION 2.8)

set(CAMIN_VERSION_MAJOR 0)
set(CAMIN_VERSION_MINOR 1)
set(CAMIN_VERSION_PATCH 1)
set(CAMIN_VERSION_STRING ${CAMIN_VERSION_MAJOR}.${CAMIN_VERSION_MINOR}.${CAMIN_VERSION_PATCH})

add_definitions( -DEFL_BETA_API_SUPPORT=1 )
find_package(PkgConfig)
pkg_check_modules(LIBXML2 libxml-2.0)
pkg_check_modules(ECORE ecore-con ecore)
pkg_check_modules(EO eo)
pkg_check_modules(LIBURIPARSER liburiparser)
configure_file( ${CMAKE_SOURCE_DIR}/include/config.h.in ${CMAKE_SOURCE_DIR}/include/config.h )
link_directories(
     ${LIBXML2_LIBRARY_DIRS} ${ECORE_LIBRARY_DIRS} ${EO_LIBRARY_DIRS} ${LIBURIPARSER_LIBRARY_DIRS}
)
include_directories(
     include/ ${LIBXML2_INCLUDE_DIRS} ${ECORE_INCLUDE_DIRS} ${EO_INCLUDE_DIRS} ${LIBURIPARSER_INCLUDE_DIRS}
)
add_subdirectory(src)


