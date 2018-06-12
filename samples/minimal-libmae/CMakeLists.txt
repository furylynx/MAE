cmake_minimum_required(VERSION 3.8)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../../cmake/Modules/JSONParser.cmake")
file(READ "${CMAKE_SOURCE_DIR}/../../mae.json" MAEJSONCONTENT)
sbeParseJson(MAEJSON MAEJSONCONTENT)

# Set package infos
set(MYEXEC minimal-libmae)

SET(MYEXEC_VERSION_MAJOR ${MAEJSON.version_major})
SET(MYEXEC_VERSION_MINOR ${MAEJSON.version_minor})
SET(MYEXEC_VERSION_PATCH ${MAEJSON.version_patch})
set(MYEXEC_VERSION_STRING ${MYEXEC_VERSION_MAJOR}.${MYEXEC_VERSION_MINOR}.${MYEXEC_VERSION_PATCH})

set(MYEXEC_DESCRIPTION "Minimal libmae test.")
set(MYEXEC_URL "https://github.com/furylynx/MAE")

set(MYEXEC_REQ_MAE LibMAE)
set(MYEXEC_REQ_MAE_V libmae)
set(MYEXEC_REQ_MAE_VERSION "${MYEXEC_VERSION_STRING}")


set(MYEXEC_REQUIRES "${MYEXEC_REQ_MAE_V} >= ${MYEXEC_REQ_MAE_VERSION}" )

# Define the project
project(${MYEXEC} VERSION ${MYEXEC_VERSION_STRING})

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SOURCE_FILES src/minimal-libmae.cpp)

set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION lib/cmake/${MYEXEC})

set(BIN_INSTALL_DIR bin/ )
set(SYSCONFIG_INSTALL_DIR etc/${MYEXEC}/ )

# We produce a shared library
add_executable(${MYEXEC} ${SOURCE_FILES})

# Install specs
install (TARGETS ${MYEXEC}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

# Import additional modules (for libxml++ and libintl)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/Modules/")

# Dependencies
find_package ( ${MYEXEC_REQ_MAE} ${MYEXEC_REQ_MAE_VERSION} REQUIRED )

set (MYEXEC_INCLUDE_DIRS ${LibMAE_INCLUDE_DIRS})
set (MYEXEC_LIBRARIES ${LibMAE_LIBRARIES} )

include_directories(${MYEXEC_INCLUDE_DIRS})
target_link_libraries (${MYEXEC} ${MYEXEC_LIBRARIES} )

# Target
set_target_properties(${MYEXEC} PROPERTIES VERSION ${MYEXEC_VERSION_STRING})

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")