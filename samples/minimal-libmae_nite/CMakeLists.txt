cmake_minimum_required(VERSION 3.6)
project(minimal_libmae_nite)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/minimal-libmae_nite.cpp)

add_executable(minimal_libmae_nite ${SOURCE_FILES})

link_directories( ${OPENNI_LIB_DIR} )
INCLUDE_DIRECTORIES( ${OPENNI_INCLUDE_DIR} )
TARGET_LINK_LIBRARIES(minimal_libmae_nite mae_nite)