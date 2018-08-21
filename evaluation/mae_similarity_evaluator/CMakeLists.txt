cmake_minimum_required(VERSION 3.8)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../../cmake/Modules/JSONParser.cmake")
file(READ "${CMAKE_SOURCE_DIR}/../../mae.json" MAEJSONCONTENT)
sbeParseJson(MAEJSON MAEJSONCONTENT)

# Set package infos
set(MYEXEC mae_similarity_evaluator)

set(MYEXEC_VERSION_MAJOR ${MAEJSON.version_major})
set(MYEXEC_VERSION_MINOR ${MAEJSON.version_minor})
set(MYEXEC_VERSION_PATCH ${MAEJSON.version_patch})
set(MYEXEC_VERSION_STRING ${MYEXEC_VERSION_MAJOR}.${MYEXEC_VERSION_MINOR}.${MYEXEC_VERSION_PATCH})

set(MYEXEC_DESCRIPTION "Evaluation tool for Labanotation scores.")
set(MYEXEC_URL "https://github.com/furylynx/MAE")

set(MYEXEC_REQ_MAE LibMAE)
set(MYEXEC_REQ_MAE_V libmae)
set(MYEXEC_REQ_MAE_VERSION ${MYEXEC_VERSION_STRING})

set(MYEXEC_REQ_BOOST Boost)
set(MYEXEC_REQ_BOOST_V libboost)
set(MYEXEC_REQ_BOOST_COMPONENT_FILESYSTEM filesystem)
set(MYEXEC_REQ_BOOST_COMPONENT_FILESYSTEM_V libboost-filesystem)
set(MYEXEC_REQ_BOOST_COMPONENT_DATE_TIME date_time)
set(MYEXEC_REQ_BOOST_COMPONENT_DATE_TIME_V libboost-date-time)
set(MYEXEC_REQ_BOOST_VERSION "1.5.3")

set(MYEXEC_REQ_SQLITE Sqlite)
set(MYEXEC_REQ_SQLITE_V sqlite3)
set(MYEXEC_REQ_SQLITE_VERSION "3.21.0")

set(MYLIB_REQ_OPENCV OpenCV)
set(MYLIB_REQ_OPENCV_V opencv)
set(MYLIB_REQ_OPENCV_VERSION "2.4.8")
# apply additional versions if actually compatible
set(MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS "2" "3")

set(MYEXEC_REQUIRES "${MYEXEC_REQ_MAE_V} >= ${MYEXEC_REQ_MAE_VERSION}, ${MYEXEC_REQ_MAE_DEMO_V} >= ${MYEXEC_REQ_MAE_DEMO_VERSION}, ${MYEXEC_REQ_BOOST_COMPONENT_FILESYSTEM_V} >= ${MYEXEC_REQ_BOOST_VERSION}, ${MYEXEC_REQ_BOOST_COMPONENT_DATE_TIME_V} >= ${MYEXEC_REQ_BOOST_VERSION}, ${MYEXEC_REQ_SQLITE} >= ${MYEXEC_REQ_SQLITE_VERSION}" )

# Define the project
project(${MYEXEC} VERSION ${MYEXEC_VERSION_STRING})

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SOURCE_FILES src/mae_similarity_evaluator.cpp
        src/file.hpp src/database.hpp src/convenience.hpp src/comparators.hpp)

INCLUDE("GNUInstallDirs")


set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION lib/cmake/${MYEXEC})

set(BIN_INSTALL_DIR ${CMAKE_INSTALL_BINDIR} )
set(SYSCONFIG_INSTALL_DIR etc/${MYLIB}/ )

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
find_package ( ${MYEXEC_REQ_BOOST} ${MYEXEC_REQ_BOOST_VERSION} COMPONENTS ${MYEXEC_REQ_BOOST_COMPONENT_FILESYSTEM} ${MYEXEC_REQ_BOOST_COMPONENT_DATE_TIME} REQUIRED )
find_package ( ${MYEXEC_REQ_SQLITE} ${MYEXEC_REQ_SQLITE_VERSION} REQUIRED )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    set (OMP_LIBRARIES ${OpenMP_CXX_LIBRARIES} ${OpenMP_C_LIBRARIES})
endif()

set (MYEXEC_INCLUDE_DIRS ${LibMAE_INCLUDE_DIRS} ${SQLITE_INCLUDE_DIR})
set (MYEXEC_LIBRARIES ${LibMAE_LIBRARIES} ${Boost_LIBRARIES} ${Boost_system_LIBRARY} ${SQLITE_LIBRARIES} ${OMP_LIBRARIES})

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


# configure cpack
# set libmae which is not found by SHLIBDEPS
SET (CPACK_DEBIAN_PACKAGE_DEPENDS "${MYEXEC_REQ_MAE_C} (>= ${MYEXEC_REQ_MAE_VERSION}), ${MYEXEC_REQ_MAE_DEMO_C} (>= ${MYEXEC_REQ_MAE_DEMO_VERSION})")
INCLUDE("${CMAKE_SOURCE_DIR}/../../cmake/Modules/MAECPack.cmake")