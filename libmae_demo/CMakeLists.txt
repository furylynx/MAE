cmake_minimum_required(VERSION 3.6)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Modules/JSONParser.cmake")
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
SET(MYLIB_REQ_MAE_VERSION ${MYLIB_VERSION_STRING})

SET(MYLIB_REQ_OPENCV OpenCV)
SET(MYLIB_REQ_OPENCV_V opencv)
SET(MYLIB_REQ_OPENCV_VERSION "2.4.8")
# apply additional versions if actually compatible
SET(MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS "2" "3")

SET(MYLIB_REQUIRES "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_SDL2_V} >= ${MYLIB_REQ_SDL2_VERSION}, ${MYLIB_REQ_SDL2_IMAGE_V}, ${MYLIB_REQ_SDL2_TTF_V}")

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


SET(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
SET(INSTALL_PACKAGE_LOCATION lib/cmake/lib${MYLIB})

SET(INCLUDE_INSTALL_DIR include/ )
SET(LIB_INSTALL_DIR lib/ )
SET(BIN_INSTALL_DIR bin/ )
SET(SYSCONFIG_INSTALL_DIR etc/${MYLIB}/ )

# We produce a shared library
ADD_LIBRARY(${MYLIB} SHARED ${SOURCE_FILES})

# Install specs
INSTALL (TARGETS ${MYLIB}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

INSTALL(DIRECTORY src/ DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING PATTERN "*.h*")

# Import additional modules (for libxml++ and libintl)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/Modules/")

# Dependencies
FIND_PACKAGE ( ${MYLIB_REQ_MAE} ${MYLIB_REQ_MAE_VERSION} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2} ${MYLIB_REQ_SDL2_VERSION} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2_IMAGE} REQUIRED )
FIND_PACKAGE ( ${MYLIB_REQ_SDL2_TTF} REQUIRED )

# fix for macos (opencv@2)
# Check OpenCV
FIND_PACKAGE ( ${MYLIB_REQ_OPENCV} REQUIRED )
if ("${${MYLIB_REQ_OPENCV}_VERSION_MAJOR}" IN_LIST MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS)
    MESSAGE( STATUS "Found OpenCV version ${${MYLIB_REQ_OPENCV}_VERSION}." )
else()
    MESSAGE( FATAL_ERROR "Cannot find a compatible OpenCV version." )
endif()


SET (MYLIB_INCLUDE_DIRS ${LibMAE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
SET (MYLIB_LIBRARIES ${LibMAE_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} )

INCLUDE_DIRECTORIES(${MYLIB_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES (${MYLIB} ${MYLIB_LIBRARIES} )

# Target
SET_target_properties(${MYLIB} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

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


# configure cpack
# set libmae which is not found by SHLIBDEPS
SET (CPACK_DEBIAN_PACKAGE_DEPENDS "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}")
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Modules/MAECPack.cmake")
