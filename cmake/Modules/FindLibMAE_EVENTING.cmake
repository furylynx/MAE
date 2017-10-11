# find libmae
#
# exports:
#
#   LibMAE_EVENTING_FOUND
#   LibMAE_EVENTING_INCLUDE_DIRS
#   LibMAE_EVENTING_LIBRARIES
#   LibMAE_EVENTING_VERSION
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(LibMAE_EVENTING_PKGCONF libmae_eventing)

if(${LibMAE_EVENTING_PKGCONF_VERSION} VERSION_LESS ${LibMAE_EVENTING_FIND_VERSION_MAJOR}.${LibMAE_EVENTING_FIND_VERSION_MINOR}.${LibMAE_EVENTING_FIND_VERSION_PATCH})

    if (${LibMAE_EVENTING_FIND_REQUIRED})
        message(SEND_ERROR "Library libmae found in version ${LibMAE_EVENTING_PKGCONF_VERSION} but version ${LibMAE_EVENTING_FIND_VERSION_MAJOR}.${LibMAE_EVENTING_FIND_VERSION_MINOR}.${LibMAE_EVENTING_FIND_VERSION_PATCH} is required.")
    else()
        set(LibMAE_EVENTING_LIBRARIES)
        set(LibMAE_EVENTING_INCLUDE_DIRS)
        set(LibMAE_EVENTING_VERSION)
        set(LibMAE_EVENTING_FOUND no)
    endif()
else()
    # Include dir
    find_path(LibMAE_EVENTING_INCLUDE_DIR
            NAMES mae/eventing/eventing.hpp
            PATHS ${LibMAE_EVENTING_PKGCONF_INCLUDE_DIRS}
            )

    # Finally the library itself
    find_library(LibMAE_EVENTING_LIBRARY
            NAMES mae_demo
            PATHS ${LibMAE_EVENTING_PKGCONF_LIBRARY_DIRS}
            )

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE_EVENTING DEFAULT_MSG LibMAE_EVENTING_LIBRARY LibMAE_EVENTING_INCLUDE_DIR)

    if(LibMAE_EVENTING_PKGCONF_FOUND)
        set(LibMAE_EVENTING_LIBRARIES ${LibMAE_EVENTING_LIBRARY} ${LibMAE_EVENTING_PKGCONF_LIBRARIES})
        set(LibMAE_EVENTING_INCLUDE_DIRS ${LibMAE_EVENTING_INCLUDE_DIR} ${LibMAE_EVENTING_PKGCONF_INCLUDE_DIRS})
        set(LibMAE_EVENTING_VERSION ${LibMAE_EVENTING_PKGCONF_VERSION})
        set(LibMAE_EVENTING_FOUND yes)
    else()
        if (${LibMAE_EVENTING_FIND_REQUIRED})
            message(SEND_ERROR "Library libmae not found.")
        else()
            set(LibMAE_EVENTING_LIBRARIES)
            set(LibMAE_EVENTING_INCLUDE_DIRS)
            set(LibMAE_EVENTING_VERSION)
            set(LibMAE_EVENTING_FOUND no)
        endif()
    endif()
endif()
