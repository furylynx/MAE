# find libmae
#
# exports:
#
#   LibMAE_FOUND
#   LibMAE_INCLUDE_DIRS
#   LibMAE_LIBRARIES
#   LibMAE_VERSION
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(LibMAE_PKGCONF libmae)

if(${LibMAE_PKGCONF_VERSION} VERSION_LESS ${LibMAE_FIND_VERSION_MAJOR}.${LibMAE_FIND_VERSION_MINOR}.${LibMAE_FIND_VERSION_PATCH})

    if (${LibMAE_FIND_REQUIRED})
        message(SEND_ERROR "Library libmae found in version ${LibMAE_PKGCONF_VERSION} but version ${LibMAE_FIND_VERSION_MAJOR}.${LibMAE_FIND_VERSION_MINOR}.${LibMAE_FIND_VERSION_PATCH} is required.")
    else()
        set(LibMAE_LIBRARIES)
        set(LibMAE_INCLUDE_DIRS)
        set(LibMAE_VERSION)
        set(LibMAE_FOUND no)
    endif()
else()
    # Include dir
    find_path(LibMAE_INCLUDE_DIR
            NAMES mae/mae.hpp
            PATHS ${LibMAE_PKGCONF_INCLUDE_DIRS}
            )

    # Finally the library itself
    find_library(LibMAE_LIBRARY
            NAMES mae
            PATHS ${LibMAE_PKGCONF_LIBRARY_DIRS}
            )

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE DEFAULT_MSG LibMAE_LIBRARY LibMAE_INCLUDE_DIR)

    if(LibMAE_PKGCONF_FOUND)
        set(LibMAE_LIBRARIES ${LibMAE_LIBRARY} ${LibMAE_PKGCONF_LIBRARIES})
        set(LibMAE_INCLUDE_DIRS ${LibMAE_INCLUDE_DIR} ${LibMAE_PKGCONF_INCLUDE_DIRS})
        set(LibMAE_VERSION ${LibMAE_PKGCONF_VERSION})
        set(LibMAE_FOUND yes)
    else()
        if (${LibMAE_FIND_REQUIRED})
            message(SEND_ERROR "Library libmae not found.")
        else()
            set(LibMAE_LIBRARIES)
            set(LibMAE_INCLUDE_DIRS)
            set(LibMAE_VERSION)
            set(LibMAE_FOUND no)
        endif()
    endif()
endif()
