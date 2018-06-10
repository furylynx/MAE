###############################################################################
# PACKAGING
###############################################################################

# PACKAGING OPTIONS: GENERAL

# This file format is used to package source code ("make package_source")
set(CPACK_SOURCE_GENERATOR "TGZ")

SET(CPACK_PACKAGE_VENDOR "furylynx")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${MYLIB_DESCRIPTION}")

# license
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")

# version
SET(CPACK_PACKAGE_VERSION_MAJOR "${MYLIB_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MYLIB_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${MYLIB_VERSION_PATCH}")

IF(APPLE)
    set(CPACK_GENERATOR PackageMaker)
elseif(UNIX)
    #
elseif(MINGW)
  set(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
  set(CPACK_NSIS_MODIFY_PATH "ON")
  set(CPACK_NSIS_CONTACT "furylynx <furylynx@example.org>")
elseif(MSVC)
  set(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
  set(CPACK_NSIS_MODIFY_PATH "ON")
  set(CPACK_NSIS_CONTACT "furylynx <furylynx@example.org>")
endif()

if(UNIX)
  if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CPACK_GENERATOR "TGZ")
    if(EXISTS "/etc/redhat-release")
      set(LINUX_NAME "")
      file(READ "/etc/redhat-release" LINUX_ISSUE)
    elseif(EXISTS "/etc/issue")
      set(LINUX_NAME "")
      file(READ "/etc/issue" LINUX_ISSUE)
    endif()
    if(DEFINED LINUX_ISSUE)
      # Fedora case
      if(LINUX_ISSUE MATCHES "Fedora")
        string(REGEX MATCH "release ([0-9]+)" FEDORA "${LINUX_ISSUE}")
        set(LINUX_NAME "FC${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Fedora")
      # Red Hat case
      if(LINUX_ISSUE MATCHES "Red")
        string(REGEX MATCH "release ([0-9]+\\.[0-9]+)" REDHAT "${LINUX_ISSUE}")
        set(LINUX_NAME "RHEL_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Red")
      # CentOS case
      if(LINUX_ISSUE MATCHES "CentOS")
        string(REGEX MATCH "release ([0-9]+\\.[0-9]+)" CENTOS "${LINUX_ISSUE}")
        set(LINUX_NAME "CentOS_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "CentOS")
      # Ubuntu case
      if(LINUX_ISSUE MATCHES "Ubuntu")
        string(REGEX MATCH "buntu ([0-9]+\\.[0-9]+)" UBUNTU "${LINUX_ISSUE}")
        set(LINUX_NAME "Ubuntu_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Ubuntu")
      # Debian case
      if(LINUX_ISSUE MATCHES "Debian")
        string(REGEX MATCH "Debian .*ux ([a-zA-Z]*/?[a-zA-Z]*) .*" DEBIAN "${LINUX_ISSUE}")
        set(LINUX_NAME "Debian_${CMAKE_MATCH_1}")
        string(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        set(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Debian")
      # Open SuSE case
      if(LINUX_ISSUE MATCHES "SUSE")
        string(REGEX MATCH "SUSE  ([0-9]+\\.[0-9]+)" SUSE "${LINUX_ISSUE}")
        set(LINUX_NAME "openSUSE_${CMAKE_MATCH_1}")
        string(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "SUSE")
    endif(DEFINED LINUX_ISSUE)
  endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif(UNIX)

# PACKAGING OPTIONS: DEB
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "furylynx")
# autogenerate dependency information
SET (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# PACKAGING OPTIONS: RPM
set(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 license")
set(CPACK_RPM_PACKAGE_VENDOR "furylynx")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_REQUIRES "${MYLIB_REQUIRES_RPM}")




INCLUDE(CPack)
