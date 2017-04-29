# find libmae
#
# exports:
#
#   LibMAE_EVENTING__FOUND
#   LibMAE_EVENTING__INCLUDE_DIRS
#   LibMAE_EVENTING__LIBRARIES
#   LibMAE_EVENTING__VERSION
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(LibMAE_EVENTING__PKGCONF libmae_eventing)

if(${LibMAE_EVENTING__PKGCONF_VERSION} VERSION_LESS ${LibMAE_EVENTING__FIND_VERSION_MAJOR}.${LibMAE_EVENTING__FIND_VERSION_MINOR}.${LibMAE_EVENTING__FIND_VERSION_PATCH})

    if (${LibMAE_EVENTING__FIND_REQUIRED})
        message(SEND_ERROR "Library libmae found in version ${LibMAE_EVENTING__PKGCONF_VERSION} but version ${LibMAE_EVENTING__FIND_VERSION_MAJOR}.${LibMAE_EVENTING__FIND_VERSION_MINOR}.${LibMAE_EVENTING__FIND_VERSION_PATCH} is required.")
    else()
        set(LibMAE_EVENTING__LIBRARIES)
        set(LibMAE_EVENTING__INCLUDE_DIRS)
        set(LibMAE_EVENTING__VERSION)
        set(LibMAE_EVENTING__FOUND no)
    endif()
else()
    # Include dir
    find_path(LibMAE_EVENTING__INCLUDE_DIR
            NAMES mae/eventing/eventing.hpp
            PATHS ${LibMAE_EVENTING__PKGCONF_INCLUDE_DIRS}
            )

    # Finally the library itself
    find_library(LibMAE_EVENTING__LIBRARY
            NAMES mae_demo
            PATHS ${LibMAE_EVENTING__PKGCONF_LIBRARY_DIRS}
            )

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE DEFAULT_MSG LibMAE_EVENTING__LIBRARY LibMAE_EVENTING__INCLUDE_DIR)

    if(LibMAE_EVENTING__PKGCONF_FOUND)
        set(LibMAE_EVENTING__LIBRARIES ${LibMAE_EVENTING__LIBRARY} ${LibMAE_EVENTING__PKGCONF_LIBRARIES})
        set(LibMAE_EVENTING__INCLUDE_DIRS ${LibMAE_EVENTING__INCLUDE_DIR} ${LibMAE_EVENTING__PKGCONF_INCLUDE_DIRS})
        set(LibMAE_EVENTING__VERSION ${LibMAE_EVENTING__PKGCONF_VERSION})
        set(LibMAE_EVENTING__FOUND yes)
    else()
        if (${LibMAE_EVENTING__FIND_REQUIRED})
            message(SEND_ERROR "Library libmae not found.")
        else()
            set(LibMAE_EVENTING__LIBRARIES)
            set(LibMAE_EVENTING__INCLUDE_DIRS)
            set(LibMAE_EVENTING__VERSION)
            set(LibMAE_EVENTING__FOUND no)
        endif()
    endif()
endif()
