# find libmae
#
# exports:
#
#   MAE_FOUND
#   MAE_INCLUDE_DIRS
#   MAE_LIBRARIES
#

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(MAE_PKGCONF REQUIRED libmae)

# Include dir
find_path(MAE_INCLUDE_DIR
        NAMES mae/mae.hpp
        PATHS ${MAE_PKGCONF_INCLUDE_DIRS}
        )

# Finally the library itself
find_library(MAE_LIBRARY
        NAMES mae
        PATHS ${MAE_PKGCONF_LIBRARY_DIRS}
        )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(MAE DEFAULT_MSG MAE_LIBRARY MAE_INCLUDE_DIR)


if(MAE_PKGCONF_FOUND)
    set(MAE_LIBRARIES ${MAE_LIBRARY} ${MAE_PKGCONF_LIBRARIES})
    set(MAE_INCLUDE_DIRS ${MAE_INCLUDE_DIR} ${MAE_PKGCONF_INCLUDE_DIRS})
    set(MAE_FOUND yes)
else()
    set(MAE_LIBRARIES)
    set(MAE_INCLUDE_DIRS)
    set(MAE_FOUND no)
endif()


