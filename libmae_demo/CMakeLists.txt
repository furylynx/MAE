cmake_minimum_required(VERSION 3.8)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Includes/JSONParser.cmake")
file(READ "${CMAKE_SOURCE_DIR}/../mae.json" MAEJSONCONTENT)
sbeParseJson(MAEJSON MAEJSONCONTENT)

# Set package infos
SET(MYLIB mae_demo)

SET(MYLIB_VERSION_MAJOR ${MAEJSON.version_major})
SET(MYLIB_VERSION_MINOR ${MAEJSON.version_minor})
SET(MYLIB_VERSION_PATCH ${MAEJSON.version_patch})
SET(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

SET(MYLIB_DESCRIPTION "Demo library of the Movement Analysis Engine (MAE) for analyzing movement using depth sensors and Labanotation.")
SET(MYLIB_URL "https://github.com/furylynx/MAE")

SET(MYLIB_REQ_SDL2 SDL2)
SET(MYLIB_REQ_SDL2_V sdl2)
SET(MYLIB_REQ_SDL2_VERSION "2.0.2")
SET(MYLIB_REQ_SDL2_IMAGE SDL2_image)
SET(MYLIB_REQ_SDL2_IMAGE_V SDL2_image)
SET(MYLIB_REQ_SDL2_TTF SDL2_ttf)
SET(MYLIB_REQ_SDL2_TTF_V SDL2_ttf)

SET(MYLIB_REQ_MAE LibMAE)
SET(MYLIB_REQ_MAE_V libmae)
SET(MYLIB_REQ_MAE_C mae)
SET(MYLIB_REQ_MAE_VERSION ${MYLIB_VERSION_STRING})

SET(MYLIB_REQUIRES "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_SDL2_V} >= ${MYLIB_REQ_SDL2_VERSION}, ${MYLIB_REQ_SDL2_IMAGE_V}, ${MYLIB_REQ_SDL2_TTF_V}")
SET(MYLIB_REQUIRES_RPM "glibc >= 2.17, libgcc >= 4.8.5, glibmm24 >= 2.50.0, libstdc++ >= 4.8.5, ${MYLIB_REQ_MAE_C} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_SDL2} >= ${MYLIB_REQ_SDL2_VERSION}, ${MYLIB_REQ_SDL2_IMAGE_V}, ${MYLIB_REQ_SDL2_TTF_V}" )

# Define the project
PROJECT(${MYLIB} VERSION ${MYLIB_VERSION_STRING})

# Use C++11
SET(CMAKE_CXX_STANDARD 11)

# Source files
SET(SOURCE_FILES src/mae/demo/demo.hpp
        src/mae/demo/fl/fl.hpp
        src/mae/demo/fl/laban_visualizer.cpp
        src/mae/demo/fl/laban_visualizer.hpp
        src/mae/demo/fl/pose_window.cpp
        src/mae/demo/fl/pose_window.hpp
        src/mae/demo/fl/recognition_window.cpp
        src/mae/demo/fl/recognition_window.hpp
        src/mae/demo/fl/recorder_window.cpp
        src/mae/demo/fl/recorder_window.hpp
        src/mae/demo/fl/res/directions_handler.cpp
        src/mae/demo/fl/res/directions_handler.hpp
        src/mae/demo/fl/res/res.hpp
        src/mae/demo/fl/sequence_window.cpp
        src/mae/demo/fl/sequence_window.hpp
        src/mae/demo/indexer_fix.hpp
        src/mae/demo/mae_res.hpp
        src/mae/demo/mae_res_img.hpp
        src/mae/demo/sdl_window.cpp
        src/mae/demo/sdl_window.hpp
        src/mae/demo/sdl_window_item.cpp
        src/mae/demo/sdl_window_item.hpp)


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
ADD_LIBRARY(${MYLIB} SHARED ${SOURCE_FILES})

if (MAE_STATIC)
    add_library(${MYLIB}Static STATIC ${SOURCE_FILES})
    set_target_properties(${MYLIB}Static PROPERTIES OUTPUT_NAME ${MYLIB})
endif()

# Install specs
INSTALL (TARGETS ${MYLIB}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    INSTALL(DIRECTORY src/ DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING PATTERN "*.h*" PATTERN "*.hh" EXCLUDE)
endif()

# Import additional modules (for libxml++ and libintl)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/Modules/")

# Dependencies
FIND_PACKAGE ( ${MYLIB_REQ_MAE} ${MYLIB_REQ_MAE_VERSION} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2} ${MYLIB_REQ_SDL2_VERSION} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2_IMAGE} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2_TTF} REQUIRED )

SET (MYLIB_INCLUDE_DIRS ${LibMAE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
SET (MYLIB_LIBRARIES ${LibMAE_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} )

INCLUDE_DIRECTORIES(${MYLIB_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES (${MYLIB} ${MYLIB_LIBRARIES} )

# Target
SET_target_properties(${MYLIB} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # package (version) info
    INCLUDE(CMakePackageConfigHelpers)
    WRITE_BASIC_PACKAGE_VERSION_FILE(
            "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
            VERSION ${MYLIB_VERSION_STRING}
            COMPATIBILITY SameMajorVersion )

    CONFIGURE_PACKAGE_CONFIG_FILE(${CMAKE_CURRENT_SOURCE_DIR}/${MYLIB}Config.cmakein ${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake
            INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cmake/${MYLIB}
            PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

    INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
            DESTINATION ${LIB_INSTALL_DIR}/${MYLIB}/cmake )

    # configure and install pkg config .pc file
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/lib${MYLIB}.pc.cmakein ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc @ONLY)
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")
endif()

# configure cpack
# set libmae which is not found by SHLIBDEPS
SET (CPACK_DEBIAN_PACKAGE_DEPENDS "${MYLIB_REQ_MAE_C} (>= ${MYLIB_REQ_MAE_VERSION})")
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Includes/MAECPack.cmake")
