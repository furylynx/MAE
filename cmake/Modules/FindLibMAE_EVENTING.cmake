# Searches for the libmae_eventing library. Uses mae_eventingConfig and, if required, also pkgconfig and the environment variable MAE_HOME.
#
# exports:
#
#   LibMAE_EVENTING_FOUND
#   LibMAE_EVENTING_INCLUDE_DIRS
#   LibMAE_EVENTING_LIBRARIES
#   LibMAE_EVENTING_VERSION
#

# search using mae_eventingConfig.cmake
if (LibMAE_EVENTING_FIND_VERSION)
  find_package(mae_eventing ${LibMAE_EVENTING_FIND_VERSION_MAJOR}.${LibMAE_EVENTING_FIND_VERSION_MINOR}.${LibMAE_EVENTING_FIND_VERSION_PATCH} CONFIG HINTS "$ENV{MAE_HOME}")
else()
  find_package(mae_eventing CONFIG HINTS "$ENV{MAE_HOME}")
endif()

if (mae_eventing_FOUND)
  set(LibMAE_EVENTING_LIBRARIES ${MAE_EVENTING_LIBRARIES})
  set(LibMAE_EVENTING_INCLUDE_DIRS ${MAE_EVENTING_INCLUDE_DIRS})
  set(LibMAE_EVENTING_VERSION ${MAE_EVENTING_VERSION})
  set(LibMAE_EVENTING_FOUND yes)

  message(STATUS "Library libmae_eventing found in version ${LibMAE_EVENTING_VERSION}.")
else()

  # search using pkgconfig
  include(FindPkgConfig)
  include(FindPackageHandleStandardArgs)

  # Use pkg-config to get hints about paths
  pkg_check_modules(LibMAE_EVENTING_PKGCONF libmae_eventing)

  if (PKG_CONFIG_FOUND AND LibMAE_EVENTING_PKGCONF_FOUND AND (NOT LibMAE_EVENTING_FIND_VERSION OR NOT ${LibMAE_EVENTING_PKGCONF_VERSION} VERSION_LESS ${LibMAE_EVENTING_FIND_VERSION_MAJOR}.${LibMAE_EVENTING_FIND_VERSION_MINOR}.${LibMAE_EVENTING_FIND_VERSION_PATCH}))

      # Include dir
      find_path(LibMAE_EVENTING_INCLUDE_DIR
              NAMES mae/eventing/eventing.hpp
              PATHS ${LibMAE_EVENTING_PKGCONF_INCLUDE_DIRS}
              )

      # Finally the library itself
      find_library(LibMAE_EVENTING_LIBRARY
              NAMES mae_eventing
              PATHS ${LibMAE_EVENTING_PKGCONF_LIBRARY_DIRS}
              )

      FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE_EVENTING DEFAULT_MSG LibMAE_EVENTING_LIBRARY LibMAE_EVENTING_INCLUDE_DIR)

      set(LibMAE_EVENTING_LIBRARIES ${LibMAE_EVENTING_LIBRARY} ${LibMAE_EVENTING_PKGCONF_LIBRARIES})
      set(LibMAE_EVENTING_INCLUDE_DIRS ${LibMAE_EVENTING_INCLUDE_DIR} ${LibMAE_EVENTING_PKGCONF_INCLUDE_DIRS})
      set(LibMAE_EVENTING_VERSION ${LibMAE_EVENTING_PKGCONF_VERSION})
      set(LibMAE_EVENTING_FOUND yes)
  else()

      # Use environment variable MAE_HOME to search package

      if("$ENV{MAE_HOME}" AND EXISTS "$ENV{MAE_HOME}/version")
          # read version from file if exists
          FILE(READ "$ENV{MAE_HOME}/version" MAE_ENV_VERSION)
      endif()

      if ("$ENV{MAE_HOME}" AND (NOT LibMAE_EVENTING_FIND_VERSION OR NOT ${MAE_ENV_VERSION} VERSION_LESS ${LibMAE_EVENTING_FIND_VERSION_MAJOR}.${LibMAE_EVENTING_FIND_VERSION_MINOR}.${LibMAE_EVENTING_FIND_VERSION_PATCH}))

          # Include dir
          find_path(LibMAE_EVENTING_INCLUDE_DIR
                  NAMES mae/eventing/eventing.hpp
                  PATHS "$ENV{MAE_HOME}/includes"
                  )

          # Finally the library itself
          find_library(LibMAE_EVENTING_LIBRARY
                  NAMES mae_eventing
                  PATHS "$ENV{MAE_HOME}/lib"
                  )

          FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMAE_EVENTING DEFAULT_MSG LibMAE_EVENTING_LIBRARY LibMAE_EVENTING_INCLUDE_DIR)

          set(LibMAE_EVENTING_LIBRARIES ${LibMAE_EVENTING_LIBRARY})
          set(LibMAE_EVENTING_INCLUDE_DIRS ${LibMAE_EVENTING_INCLUDE_DIR})
          set(LibMAE_EVENTING_VERSION ${MAE_ENV_VERSION})
          set(LibMAE_EVENTING_FOUND yes)
      else()
          if (${LibMAE_EVENTING_FIND_REQUIRED})
              message(SEND_ERROR "Library libmae_eventing not found.")
          else()
              set(LibMAE_EVENTING_LIBRARIES)
              set(LibMAE_EVENTING_INCLUDE_DIRS)
              set(LibMAE_EVENTING_VERSION)
              set(LibMAE_EVENTING_FOUND no)
          endif()
      endif()
  endif()
endif()
