INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_A3SAT a3sat)

FIND_PATH(
    A3SAT_INCLUDE_DIRS
    NAMES a3sat/api.h
    HINTS $ENV{A3SAT_DIR}/include
        ${PC_A3SAT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    A3SAT_LIBRARIES
    NAMES gnuradio-a3sat
    HINTS $ENV{A3SAT_DIR}/lib
        ${PC_A3SAT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/a3satTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(A3SAT DEFAULT_MSG A3SAT_LIBRARIES A3SAT_INCLUDE_DIRS)
MARK_AS_ADVANCED(A3SAT_LIBRARIES A3SAT_INCLUDE_DIRS)
