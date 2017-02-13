cmake_minimum_required(VERSION 3.6)
project(mae_demo)

# Set the version
set(MYLIB_VERSION_MAJOR 0)
set(MYLIB_VERSION_MINOR 10)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

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

# We produce a shared library
add_library(mae_demo SHARED ${SOURCE_FILES})

# Install specs
install (TARGETS mae_demo
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        )

install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h*")


# Import additional modules (for libxml++ and libintl)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Dependencies
find_package ( mae 0.10.0 REQUIRED )
find_package ( SDL2 REQUIRED )
find_package ( SDL2_image REQUIRED )
find_package ( SDL2_ttf REQUIRED )

include_directories(${SDL2_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS})
target_link_libraries (mae_demo ${SDL2_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES})

# Target
set_target_properties(mae_demo PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

