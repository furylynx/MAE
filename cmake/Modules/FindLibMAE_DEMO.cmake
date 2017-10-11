# find libmae
#
# exports:
#
#   LibMAE_DEMO_FOUND
#   LibMAE_DEMO_INCLUDE_DIRS
#   LibMAE_DEMO_LIBRARIES
#   LibMAE_DEMO_VERSION
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(LibMAE_DEMO_PKGCONF libmae_demo)

if(${LibMAE_DEMO_PKGCONF_VERSION} VERSION_LESS ${LibMAE_DEMO_FIND_VERSION_MAJOR}.${LibMAE_DEMO_FIND_VERSION_MINOR}.${LibMAE_DEMO_FIND_VERSION_PATCH})

    if (${LibMAE_DEMO_FIND_REQUIRED})
        message(SEND_ERROR "Library libmae found in version ${LibMAE_DEMO_PKGCONF_VERSION} but version ${LibMAE_DEMO_FIND_VERSION_MAJOR}.${LibMAE_DEMO_FIND_VERSION_MINOR}.${LibMAE_DEMO_FIND_VERSION_PATCH} is required.")
    else()
        set(LibMAE_DEMO_LIBRARIES)
        set(LibMAE_DEMO_INCLUDE_DIRS)
        set(LibMAE_DEMO_VERSION)
        set(LibMAE_DEMO_FOUND no)
    endif()
else()
    # Include dir
    find_path(LibMAE_DEMO_INCLUDE_DIR
            NAMES mae/demo/demo.hpp
            PATHS ${LibMAE_DEMO_PKGCONF_INCLUDE_DIRS}
            )

    # Finally the library itself
    find_library(LibMAE_DEMO_LIBRARY
            NAMES mae_demo
            PATHS ${LibMAE_DEMO_PKGCONF_LIBRARY_DIRS}
            )

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE_DEMO DEFAULT_MSG LibMAE_DEMO_LIBRARY LibMAE_DEMO_INCLUDE_DIR)

    if(LibMAE_DEMO_PKGCONF_FOUND)
        set(LibMAE_DEMO_LIBRARIES ${LibMAE_DEMO_LIBRARY} ${LibMAE_DEMO_PKGCONF_LIBRARIES})
        set(LibMAE_DEMO_INCLUDE_DIRS ${LibMAE_DEMO_INCLUDE_DIR} ${LibMAE_DEMO_PKGCONF_INCLUDE_DIRS})
        set(LibMAE_DEMO_VERSION ${LibMAE_DEMO_PKGCONF_VERSION})
        set(LibMAE_DEMO_FOUND yes)
    else()
        if (${LibMAE_DEMO_FIND_REQUIRED})
            message(SEND_ERROR "Library libmae not found.")
        else()
            set(LibMAE_DEMO_LIBRARIES)
            set(LibMAE_DEMO_INCLUDE_DIRS)
            set(LibMAE_DEMO_VERSION)
            set(LibMAE_DEMO_FOUND no)
        endif()
    endif()
endif()
