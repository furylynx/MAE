# find librsvg-2.0
#
# exports:
#
#   RSVG2_FOUND
#   RSVG2_INCLUDE_DIRS
#   RSVG2_LIBRARIES
#   RSVG2_VERSION
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(RSVG2_PKGCONF librsvg-2.0)

if(${RSVG2_PKGCONF_VERSION} VERSION_LESS ${RSVG2_FIND_VERSION_MAJOR}.${RSVG2_FIND_VERSION_MINOR}.${RSVG2_FIND_VERSION_PATCH})

    if (${RSVG2_FIND_REQUIRED})
        message(SEND_ERROR "Library librsvg2 found in version ${RSVG2_PKGCONF_VERSION} but version ${RSVG2_FIND_VERSION_MAJOR}.${RSVG2_FIND_VERSION_MINOR}.${RSVG2_FIND_VERSION_PATCH} is required.")
    else()
        set(RSVG2_LIBRARIES)
        set(RSVG2_INCLUDE_DIRS)
        set(RSVG2_VERSION)
        set(RSVG2_FOUND no)
    endif()
else()
    # Include dir
    find_path(RSVG2_INCLUDE_DIR
            NAMES librsvg/rsvg.h
            PATHS ${RSVG2_PKGCONF_INCLUDE_DIRS} ${RSVG2_PKGCONF_INCLUDE_DIRS}/librsvg-2.0/
            )

    # Finally the library itself
    find_library(RSVG2_LIBRARY
            NAMES rsvg-2
            PATHS ${RSVG2_PKGCONF_LIBRARY_DIRS}
            )

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(RSVG2 DEFAULT_MSG RSVG2_LIBRARY RSVG2_INCLUDE_DIR)

    if(RSVG2_PKGCONF_FOUND)
        set(RSVG2_LIBRARIES ${RSVG2_LIBRARY} ${RSVG2_PKGCONF_LIBRARIES})
        set(RSVG2_INCLUDE_DIRS ${RSVG2_INCLUDE_DIR} ${RSVG2_PKGCONF_INCLUDE_DIRS})
        set(RSVG2_VERSION ${RSVG2_PKGCONF_VERSION})
        set(RSVG2_FOUND yes)
    else()
        if (${RSVG2_FIND_REQUIRED})
            message(SEND_ERROR "Library librsvg2 not found.")
        else()
            set(RSVG2_LIBRARIES)
            set(RSVG2_INCLUDE_DIRS)
            set(RSVG2_VERSION)
            set(RSVG2_FOUND no)
        endif()
    endif()
endif()
