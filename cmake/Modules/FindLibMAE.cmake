# Searches for the libmae library. Uses maeConfig and, if required, also pkgconfig and the environment variable MAE_HOME.
#
# exports:
#
#   LibMAE_FOUND
#   LibMAE_INCLUDE_DIRS
#   LibMAE_LIBRARIES
#   LibMAE_VERSION
#

# fix for vcpkg
if (DEFINED ENV{VCPKG_ROOT} OR CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg.cmake$" OR WITH_VCPKG)
  find_package ( OpenCV REQUIRED )
endif()

# search using maeConfig.cmake
if (LibMAE_FIND_VERSION)
  find_package(mae ${LibMAE_FIND_VERSION_MAJOR}.${LibMAE_FIND_VERSION_MINOR}.${LibMAE_FIND_VERSION_PATCH} CONFIG HINTS "$ENV{MAE_HOME}")
else()
  find_package(mae CONFIG HINTS "$ENV{MAE_HOME}")
endif()

if (mae_FOUND)

  # Finally the library itself
  find_library(LibMAE_LIBRARY
          NAMES mae
          PATHS ${MAE_LIB_DIRS}
          )

  set(LibMAE_LIBRARIES ${MAE_LIBRARY} ${LibMAE_LIBRARY})
  set(LibMAE_INCLUDE_DIRS ${MAE_INCLUDE_DIRS})
  set(LibMAE_VERSION ${MAE_VERSION})
  set(LibMAE_FOUND yes)

  message(STATUS "Library libmae found in version ${LibMAE_VERSION} (${LibMAE_LIBRARY}).")
else()

  # search using pkgconfig
  include(FindPkgConfig)
  include(FindPackageHandleStandardArgs)

  # Use pkg-config to get hints about paths
  pkg_check_modules(LibMAE_PKGCONF libmae)

  if (PKG_CONFIG_FOUND AND LibMAE_PKGCONF_FOUND AND (NOT LibMAE_FIND_VERSION OR NOT ${LibMAE_PKGCONF_VERSION} VERSION_LESS ${LibMAE_FIND_VERSION_MAJOR}.${LibMAE_FIND_VERSION_MINOR}.${LibMAE_FIND_VERSION_PATCH}))

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

      set(LibMAE_LIBRARIES ${LibMAE_LIBRARY} ${LibMAE_PKGCONF_LIBRARIES})
      set(LibMAE_INCLUDE_DIRS ${LibMAE_INCLUDE_DIR} ${LibMAE_PKGCONF_INCLUDE_DIRS})
      set(LibMAE_VERSION ${LibMAE_PKGCONF_VERSION})
      set(LibMAE_FOUND yes)
  else()

      # Use environment variable MAE_HOME to search package

      if("$ENV{MAE_HOME}" AND EXISTS "$ENV{MAE_HOME}/version")
          # read version from file if exists
          FILE(READ "$ENV{MAE_HOME}/version" MAE_ENV_VERSION)
      endif()

      if ("$ENV{MAE_HOME}" AND (NOT LibMAE_FIND_VERSION OR NOT ${MAE_ENV_VERSION} VERSION_LESS ${LibMAE_FIND_VERSION_MAJOR}.${LibMAE_FIND_VERSION_MINOR}.${LibMAE_FIND_VERSION_PATCH}))

          # Include dir
          find_path(LibMAE_INCLUDE_DIR
                  NAMES mae/mae.hpp
                  PATHS "$ENV{MAE_HOME}/includes"
                  )

          # Finally the library itself
          find_library(LibMAE_LIBRARY
                  NAMES mae
                  PATHS "$ENV{MAE_HOME}/lib"
                  )

          FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE DEFAULT_MSG LibMAE_LIBRARY LibMAE_INCLUDE_DIR)

          set(LibMAE_LIBRARIES ${LibMAE_LIBRARY})
          set(LibMAE_INCLUDE_DIRS ${LibMAE_INCLUDE_DIR})
          set(LibMAE_VERSION ${MAE_ENV_VERSION})
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
endif()
