cmake_minimum_required(VERSION 3.6)

# Set package infos
set(MYEXEC tutorial-listeners)

set(MYEXEC_VERSION_MAJOR 0)
set(MYEXEC_VERSION_MINOR 1)
set(MYEXEC_VERSION_PATCH 1)
set(MYEXEC_VERSION_STRING ${MYEXEC_VERSION_MAJOR}.${MYEXEC_VERSION_MINOR}.${MYEXEC_VERSION_PATCH})

set(MYEXEC_DESCRIPTION "Labanotation listeners tutorial.")
set(MYEXEC_URL "https://github.com/furylynx/MAE")

set(MYEXEC_REQ_MAE LibMAE)
set(MYEXEC_REQ_MAE_V libmae)
set(MYEXEC_REQ_MAE_VERSION "0.10.1")


set(MYEXEC_REQUIRES "${MYEXEC_REQ_MAE_V} >= ${MYEXEC_REQ_MAE_VERSION}" )

# Define the project
project(${MYEXEC} VERSION ${MYEXEC_VERSION_STRING})

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SOURCE_FILES src/tutorial-listeners.cpp
        src/recognition_listener.hpp
        src/recognition_listener.cpp
                 )

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
set (MYEXEC_LIBRARIES ${LibMAE_LIBRARIES})

include_directories(${MYEXEC_INCLUDE_DIRS})
target_link_libraries (${MYEXEC} ${MYEXEC_LIBRARIES} )

# Target
set_target_properties(${MYEXEC} PROPERTIES VERSION ${MYEXEC_VERSION_STRING})
