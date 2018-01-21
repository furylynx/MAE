cmake_minimum_required(VERSION 3.6)

# Set package infos
set(MYLIB mae_demo)

set(MYLIB_VERSION_MAJOR 0)
set(MYLIB_VERSION_MINOR 10)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(MYLIB_DESCRIPTION "Demo library of the Movement Analysis Engine (MAE) for analyzing movement using depth sensors and Labanotation.")
set(MYLIB_URL "https://github.com/furylynx/MAE")

set(MYLIB_REQ_SDL2 SDL2)
set(MYLIB_REQ_SDL2_V sdl2)
set(MYLIB_REQ_SDL2_VERSION "2.0.2")
set(MYLIB_REQ_SDL2_IMAGE SDL2_image)
set(MYLIB_REQ_SDL2_IMAGE_V SDL2_image)
set(MYLIB_REQ_SDL2_TTF SDL2_ttf)
set(MYLIB_REQ_SDL2_TTF_V SDL2_ttf)

set(MYLIB_REQ_MAE LibMAE)
set(MYLIB_REQ_MAE_V libmae)
set(MYLIB_REQ_MAE_VERSION "0.10.0")

set(MYLIB_REQ_OPENCV OpenCV)
set(MYLIB_REQ_OPENCV_V opencv)
set(MYLIB_REQ_OPENCV_VERSION "2.4.8")
# apply additional versions if actually compatible
set(MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS "2" "3")

set(MYLIB_REQUIRES "${MYLIB_REQ_MAE_V} >= ${MYLIB_REQ_MAE_VERSION}, ${MYLIB_REQ_SDL2_V} >= ${MYLIB_REQ_SDL2_VERSION}, ${MYLIB_REQ_SDL2_IMAGE_V}, ${MYLIB_REQ_SDL2_TTF_V}")

# Define the project
project(${MYLIB} VERSION ${MYLIB_VERSION_STRING})

# Use C++11
set(CMAKE_CXX_STANDARD 11)

# Source files
set(SOURCE_FILES src/mae/demo/demo.hpp
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


set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION lib/cmake/lib${MYLIB})

set(INCLUDE_INSTALL_DIR include/ )
set(LIB_INSTALL_DIR lib/ )
set(BIN_INSTALL_DIR bin/ )
set(SYSCONFIG_INSTALL_DIR etc/${MYLIB}/ )

# We produce a shared library
add_library(${MYLIB} SHARED ${SOURCE_FILES})

# Install specs
install (TARGETS ${MYLIB}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

install(DIRECTORY src/ DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING PATTERN "*.h*")


# Import additional modules (for libxml++ and libintl)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/Modules/")

# Dependencies
find_package ( ${MYLIB_REQ_MAE} ${MYLIB_REQ_MAE_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_SDL2} ${MYLIB_REQ_SDL2_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_SDL2_IMAGE} REQUIRED )
find_package ( ${MYLIB_REQ_SDL2_TTF} REQUIRED )

# fix for macos (opencv@2)
# Check OpenCV
find_package ( ${MYLIB_REQ_OPENCV} REQUIRED )
if ("${${MYLIB_REQ_OPENCV}_VERSION_MAJOR}" IN_LIST MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS)
    message( STATUS "Found OpenCV version ${${MYLIB_REQ_OPENCV}_VERSION}." )
else()
    message( FATAL_ERROR "Cannot find a compatible OpenCV version." )
endif()


set (MYLIB_INCLUDE_DIRS ${LibMAE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
set (MYLIB_LIBRARIES ${LibMAE_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} )

include_directories(${MYLIB_INCLUDE_DIRS})
target_link_libraries (${MYLIB} ${MYLIB_LIBRARIES} )

# Target
set_target_properties(${MYLIB} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

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
