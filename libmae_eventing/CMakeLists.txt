cmake_minimum_required(VERSION 3.8)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Includes/JSONParser.cmake")
file(READ "${CMAKE_SOURCE_DIR}/../mae.json" MAEJSONCONTENT)
sbeParseJson(MAEJSON MAEJSONCONTENT)

# Set package infos
set(MYLIB mae_eventing)

SET(MYLIB_VERSION_MAJOR ${MAEJSON.version_major})
SET(MYLIB_VERSION_MINOR ${MAEJSON.version_minor})
SET(MYLIB_VERSION_PATCH ${MAEJSON.version_patch})
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(MYLIB_DESCRIPTION "Eventing library of the Movement Analysis Engine (MAE) for analyzing movement using depth sensors and Labanotation.")
set(MYLIB_URL "https://github.com/furylynx/MAE")

set(MYLIB_REQ_BOOST Boost)
set(MYLIB_REQ_BOOST_V libboost)
set(MYLIB_REQ_BOOST_R boost)
set(MYLIB_REQ_BOOST_COMPONENT system)
set(MYLIB_REQ_BOOST_COMPONENT_V libboost-system)
set(MYLIB_REQ_BOOST_VERSION "1.5.3")

set(MYLIB_REQ_LIBXMLPP "LibXML++")
set(MYLIB_REQ_LIBXMLPP_V "libxml++-2.6")
set(MYLIB_REQ_LIBXMLPP_R "libxml++")
set(MYLIB_REQ_LIBXMLPP_VERSION "2.6")

set(MYLIB_REQ_MAE LibMAE)
set(MYLIB_REQ_MAE_V libmae)
SET(MYLIB_REQ_MAE_C mae)
set(MYLIB_REQ_MAE_VERSION "${MYLIB_VERSION_STRING}")

set(MYLIB_REQUIRES "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_LIBXMLPP_V} >= ${MYLIB_REQ_LIBXMLPP_VERSION}")
#set(MYLIB_REQUIRES "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_LIBXMLPP_V} >= ${MYLIB_REQ_LIBXMLPP_VERSION}, ${MYLIB_REQ_BOOST_COMPONENT_V} >= ${MYLIB_REQ_BOOST_VERSION}")
SET(MYLIB_REQUIRES_RPM "glibc >= 2.17, libgcc >= 4.8.5, glibmm24 >= 2.50.0, libstdc++ >= 4.8.5, ${MYLIB_REQ_MAE_C} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_LIBXMLPP_R} >= ${MYLIB_REQ_LIBXMLPP_VERSION}, ${MYLIB_REQ_BOOST_R} >= ${MYLIB_REQ_BOOST_VERSION}" )

# Define the project
project(${MYLIB} VERSION ${MYLIB_VERSION_STRING})

# Use C++11
set(CMAKE_CXX_STANDARD 11)

# Source files
set(SOURCE_FILES src/mae/eventing/client.hpp
        src/mae/eventing/cs_base.cpp
        src/mae/eventing/cs_base.hpp
        src/mae/eventing/eventing.hpp
        src/mae/eventing/fl/fl.hpp
        src/mae/eventing/fl/fl_client.cpp
        src/mae/eventing/fl/fl_client.hpp
        src/mae/eventing/fl/fl_server.cpp
        src/mae/eventing/fl/fl_server.hpp
        src/mae/eventing/fl/laban_serializer.cpp
        src/mae/eventing/fl/laban_serializer.hpp
        src/mae/eventing/i_registration_manager.hpp
        src/mae/eventing/i_sequence_serializer.hpp
        src/mae/eventing/indexer_fix.hpp
        src/mae/eventing/mxml.cpp
        src/mae/eventing/mxml.hpp
        src/mae/eventing/server.hpp)


INCLUDE("GNUInstallDirs")

set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION ${CMAKE_INSTALL_LIBDIR}/cmake/lib${MYLIB})

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR} )
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR} )
set(BIN_INSTALL_DIR ${CMAKE_INSTALL_BINDIR} )
set(SYSCONFIG_INSTALL_DIR etc/${MYLIB}/ )

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# We produce a shared library
add_library(${MYLIB} SHARED ${SOURCE_FILES})

if (MAE_STATIC)
    add_library(${MYLIB}Static STATIC ${SOURCE_FILES})
    set_target_properties(${MYLIB}Static PROPERTIES OUTPUT_NAME ${MYLIB})
endif()

# Install specs
install (TARGETS ${MYLIB}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(DIRECTORY src/ DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING PATTERN "*.h*" PATTERN "*.hh" EXCLUDE)
endif()

# Import additional modules (for libxml++ and libintl)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/Modules/")

# Dependencies
find_package ( ${MYLIB_REQ_MAE} ${MYLIB_REQ_MAE_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_LIBXMLPP} ${MYLIB_REQ_LIBXMLPP_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_BOOST} ${MYLIB_REQ_BOOST_VERSION} COMPONENTS ${MYLIB_REQ_BOOST_COMPONENT} REQUIRED )

set (MYLIB_INCLUDE_DIRS ${LibXML++_INCLUDE_DIRS} ${LibMAE_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set (MYLIB_LIBRARIES ${LibMAE_LIBRARIES} ${LibXML++_LIBRARIES} ${Boost_LIBRARIES} ${Boost_system_LIBRARY})

if (WIN32 AND NOT DEFINED ENV{VCPKG_ROOT} AND NOT CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg.cmake$" AND NOT WITH_VCPKG)
    #fix for mingw (link to wsock32 and ws_32)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)

    set(MYLIB_LIBRARIES ${MYLIB_LIBRARIES} ${WSOCK32_LIBRARY} ${WS2_32_LIBRARY})
endif()

include_directories(${MYLIB_INCLUDE_DIRS})
target_link_libraries (${MYLIB} ${MYLIB_LIBRARIES} )

# Target
set_target_properties(${MYLIB} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # package (version) info
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
            VERSION ${MYLIB_VERSION_STRING}
            COMPATIBILITY SameMajorVersion )

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/${MYLIB}Config.cmakein ${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake
            INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cmake/${MYLIB}
            PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
            DESTINATION ${LIB_INSTALL_DIR}/${MYLIB}/cmake )

    # configure and install pkg config .pc file
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib${MYLIB}.pc.cmakein ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")
endif()

# configure cpack
# set libmae which is not found by SHLIBDEPS
SET (CPACK_DEBIAN_PACKAGE_DEPENDS "${MYLIB_REQ_MAE_C} (>= ${MYLIB_REQ_MAE_VERSION})")
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Includes/MAECPack.cmake")
