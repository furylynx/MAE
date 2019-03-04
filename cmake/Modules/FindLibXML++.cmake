# Searches for libxml++ using either pkgconfig or vcpkg.
#
# exports:
#
#   LibXML++_FOUND
#   LibXML++_INCLUDE_DIRS
#   LibXML++_LIBRARIES
#

if (DEFINED ENV{VCPKG_ROOT} OR CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg.cmake$" )
    #vcpkg is used to find the library

    find_path(GLIBMM_INCLUDE_DIR NAMES glibmm.h)
    find_library(GLIBMM_LIBRARY NAMES glibmm)
    find_library(GIOMM_LIBRARY NAMES giomm)
    find_library(GLIB_LIBRARY NAMES glib glib-2.0)
    find_library(GIO_LIBRARY NAMES gio gio-2.0)
    find_library(GMODULE_LIBRARY NAMES gmodule gmodule-2.0)
    find_library(GOBJECT_LIBRARY NAMES gobject gobject-2.0)
    find_library(SIGCPP_LIBRARY NAMES sigc sigc-2.0)
    find_library(FFI_LIBRARY NAMES ffi libffi)
    find_library(PCRE_LIBRARY NAMES pcre libpcre)
    find_package(LibXml2 REQUIRED)
    find_package(LibLZMA REQUIRED)
    find_package(ZLIB REQUIRED)

    # Include dir
    find_path(LibXML++_INCLUDE_DIR
      NAMES libxml++/libxml++.h
    )

    # Finally the library itself
    find_library(LibXML++_LIBRARY
      NAMES xml++ xml++-2.6
    )

    if (LibXML++_INCLUDE_DIR STREQUAL "LibXML++_INCLUDE_DIR-NOTFOUND")
        if (${LibXML++_FIND_REQUIRED})
            message(SEND_ERROR "Library libxml++ not found using vcpkg.")
        else()
            set(LibXML++_LIBRARIES)
            set(LibXML++_INCLUDE_DIRS)
            set(LibXML++_VERSION)
            set(LibXML++_FOUND no)
        endif()
    else()
        set(LibXML++_LIBRARIES ${LibXML++_LIBRARY}
            ${GIOMM_LIBRARY}
            ${GLIBMM_LIBRARY}
            ${GMODULE_LIBRARY}
            ${GOBJECT_LIBRARY}
            ${GIO_LIBRARY}
            ${GLIB_LIBRARY}
            ${SIGCPP_LIBRARY}
            ${FFI_LIBRARY}
            ${LIBXML2_LIBRARIES}
            ${PCRE_LIBRARY}
            ${LIBLZMA_LIBRARIES}
            ZLIB::ZLIB)
        set(LibXML++_INCLUDE_DIRS ${LibXML++_INCLUDE_DIR} ${GLIBMM_INCLUDE_DIR} ${LIBXML2_INCLUDE_DIRS} ${LIBLZMA_INCLUDE_DIRS})
        set(LibXML++_FOUND yes)

        if (LibXML++_FIND_VERSION)
            message(WARNING "Found libxml++ using vcpkg. Thus, could not check the version. Will continue anyway.")
        else()
            message(STATUS "Found libxml++ using vcpkg.")
        endif()

    endif()
else()
    include(FindPkgConfig)
    include(FindPackageHandleStandardArgs)

    # Use pkg-config to get hints about paths
    pkg_check_modules(LibXML++_PKGCONF libxml++-2.6)

    if(${LibXML++_PKGCONF_VERSION} VERSION_LESS ${LibXML++_FIND_VERSION_MAJOR}.${LibXML++_FIND_VERSION_MINOR}.${LibXML++_FIND_VERSION_PATCH})

        if (${LibXML++_FIND_REQUIRED})
            message(SEND_ERROR "Library libxml++ found in version ${LibXML++_PKGCONF_VERSION} but version ${LibXML++_FIND_VERSION_MAJOR}.${LibXML++_FIND_VERSION_MINOR}.${LibXML++_FIND_VERSION_PATCH} is required.")
        else()
            set(LibXML++_LIBRARIES)
            set(LibXML++_INCLUDE_DIRS)
            set(LibXML++_VERSION)
            set(LibXML++_FOUND no)
        endif()
    else()

        # Include dir
        find_path(LibXML++_INCLUDE_DIR
          NAMES libxml++/libxml++.h
          PATHS ${LibXML++_PKGCONF_INCLUDE_DIRS}
        )

        # Finally the library itself
        find_library(LibXML++_LIBRARY
          NAMES xml++ xml++-2.6
          PATHS ${LibXML++_PKGCONF_LIBRARY_DIRS}
        )

        FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXML++ DEFAULT_MSG LibXML++_LIBRARY LibXML++_INCLUDE_DIR)


        if(LibXML++_PKGCONF_FOUND)
          set(LibXML++_LIBRARIES ${LibXML++_LIBRARY} ${LibXML++_PKGCONF_LIBRARIES})
          set(LibXML++_INCLUDE_DIRS ${LibXML++_INCLUDE_DIR} ${LibXML++_PKGCONF_INCLUDE_DIRS})
          set(LibXML++_FOUND yes)
        else()
            if (${LibXML++_FIND_REQUIRED})
                message(SEND_ERROR "Library libxml++ not found.")
            else()
                  set(LibXML++_LIBRARIES)
                  set(LibXML++_INCLUDE_DIRS)
                  set(LibXML++_FOUND no)
            endif()
        endif()

        # Set the include dir variables and the libraries and let libfind_process do the rest.
        # NOTE: Singular variables for this library, plural for libraries this this lib depends on.
        #set(LibXML++_PROCESS_INCLUDES LibXML++_INCLUDE_DIR)
        #set(LibXML++_PROCESS_LIBS LibXML++_LIBRARY)
    endif()
endif()
