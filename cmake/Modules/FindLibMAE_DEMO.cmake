# Searches for the libmae_demo library. Uses mae_demoConfig and, if required, also pkgconfig and the environment variable MAE_HOME.
#
# exports:
#
#   LibMAE_DEMO_FOUND
#   LibMAE_DEMO_INCLUDE_DIRS
#   LibMAE_DEMO_LIBRARIES
#   LibMAE_DEMO_VERSION
#

# search using mae_demoConfig.cmake
if (LibMAE_DEMO_FIND_VERSION)
  find_package(mae_demo ${LibMAE_DEMO_FIND_VERSION_MAJOR}.${LibMAE_DEMO_FIND_VERSION_MINOR}.${LibMAE_DEMO_FIND_VERSION_PATCH} CONFIG HINTS "$ENV{MAE_HOME}")
else()
  find_package(mae_demo CONFIG HINTS "$ENV{MAE_HOME}")
endif()

if (mae_demo_FOUND)
  set(LibMAE_DEMO_LIBRARIES ${MAE_DEMO_LIBRARIES})
  set(LibMAE_DEMO_INCLUDE_DIRS ${MAE_DEMO_INCLUDE_DIRS})
  set(LibMAE_DEMO_VERSION ${MAE_DEMO_VERSION})
  set(LibMAE_DEMO_FOUND yes)

  message(STATUS "Library libmae_demo found in version ${LibMAE_DEMO_VERSION}.")
else()

  # search using pkgconfig
  include(FindPkgConfig)
  include(FindPackageHandleStandardArgs)

  # Use pkg-config to get hints about paths
  pkg_check_modules(LibMAE_DEMO_PKGCONF libmae_demo)

  if (PKG_CONFIG_FOUND AND LibMAE_DEMO_PKGCONF_FOUND AND (NOT LibMAE_DEMO_FIND_VERSION OR NOT ${LibMAE_DEMO_PKGCONF_VERSION} VERSION_LESS ${LibMAE_DEMO_FIND_VERSION_MAJOR}.${LibMAE_DEMO_FIND_VERSION_MINOR}.${LibMAE_DEMO_FIND_VERSION_PATCH}))

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

      set(LibMAE_DEMO_LIBRARIES ${LibMAE_DEMO_LIBRARY} ${LibMAE_DEMO_PKGCONF_LIBRARIES})
      set(LibMAE_DEMO_INCLUDE_DIRS ${LibMAE_DEMO_INCLUDE_DIR} ${LibMAE_DEMO_PKGCONF_INCLUDE_DIRS})
      set(LibMAE_DEMO_VERSION ${LibMAE_DEMO_PKGCONF_VERSION})
      set(LibMAE_DEMO_FOUND yes)
  else()

      # Use environment variable MAE_HOME to search package

      if("$ENV{MAE_HOME}" AND EXISTS "$ENV{MAE_HOME}/version")
          # read version from file if exists
          FILE(READ "$ENV{MAE_HOME}/version" MAE_ENV_VERSION)
      endif()

      if ("$ENV{MAE_HOME}" AND (NOT LibMAE_DEMO_FIND_VERSION OR NOT ${MAE_ENV_VERSION} VERSION_LESS ${LibMAE_DEMO_FIND_VERSION_MAJOR}.${LibMAE_DEMO_FIND_VERSION_MINOR}.${LibMAE_DEMO_FIND_VERSION_PATCH}))

          # Include dir
          find_path(LibMAE_DEMO_INCLUDE_DIR
                  NAMES mae/demo/demo.hpp
                  PATHS "$ENV{MAE_HOME}/includes"
                  )

          # Finally the library itself
          find_library(LibMAE_DEMO_LIBRARY
                  NAMES mae_demo
                  PATHS "$ENV{MAE_HOME}/lib"
                  )

          FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE_DEMO DEFAULT_MSG LibMAE_DEMO_LIBRARY LibMAE_DEMO_INCLUDE_DIR)

          set(LibMAE_DEMO_LIBRARIES ${LibMAE_DEMO_LIBRARY})
          set(LibMAE_DEMO_INCLUDE_DIRS ${LibMAE_DEMO_INCLUDE_DIR})
          set(LibMAE_DEMO_VERSION ${MAE_ENV_VERSION})
          set(LibMAE_DEMO_FOUND yes)
      else()
          if (${LibMAE_DEMO_FIND_REQUIRED})
              message(SEND_ERROR "Library libmae_demo not found.")
          else()
              set(LibMAE_DEMO_LIBRARIES)
              set(LibMAE_DEMO_INCLUDE_DIRS)
              set(LibMAE_DEMO_VERSION)
              set(LibMAE_DEMO_FOUND no)
          endif()
      endif()
  endif()
endif()
