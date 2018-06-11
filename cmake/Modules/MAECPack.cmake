###############################################################################
# PACKAGING
###############################################################################

# PACKAGING OPTIONS: GENERAL

#SET(CPACK_SET_DESTDIR TRUE)
# This file format is used to package source code ("make package_source")
SET(CPACK_SOURCE_GENERATOR "TGZ")

SET(CPACK_PACKAGE_VENDOR "furylynx")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${MYLIB_DESCRIPTION}")

# license
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")

# version
SET(CPACK_PACKAGE_VERSION_MAJOR "${MYLIB_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MYLIB_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${MYLIB_VERSION_PATCH}")

IF(APPLE)
    SET(CPACK_GENERATOR PackageMaker)
elseif(UNIX)
    #
elseif(MINGW)
  #SET(CPACK_SET_DESTDIR FALSE)
  SET(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
  SET(CPACK_NSIS_MODIFY_PATH "ON")
  SET(CPACK_NSIS_CONTACT "furylynx <furylynx@example.org>")
elseif(MSVC)
  #SET(CPACK_SET_DESTDIR FALSE)
  SET(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
  SET(CPACK_NSIS_MODIFY_PATH "ON")
  SET(CPACK_NSIS_CONTACT "furylynx <furylynx@example.org>")
endif()

if(UNIX)
  if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(CPACK_GENERATOR "TGZ")
    if(EXISTS "/etc/redhat-release")
      SET(LINUX_NAME "")
      file(READ "/etc/redhat-release" LINUX_ISSUE)
    elseif(EXISTS "/etc/issue")
      SET(LINUX_NAME "")
      file(READ "/etc/issue" LINUX_ISSUE)
    endif()
    if(DEFINED LINUX_ISSUE)
      # Fedora case
      if(LINUX_ISSUE MATCHES "Fedora")
        STRING(REGEX MATCH "release ([0-9]+)" FEDORA "${LINUX_ISSUE}")
        SET(LINUX_NAME "FC${CMAKE_MATCH_1}")
        SET(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Fedora")
      # Red Hat case
      if(LINUX_ISSUE MATCHES "Red")
        STRING(REGEX MATCH "release ([0-9]+\\.[0-9]+)" REDHAT "${LINUX_ISSUE}")
        SET(LINUX_NAME "RHEL_${CMAKE_MATCH_1}")
        SET(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Red")
      # CentOS case
      if(LINUX_ISSUE MATCHES "CentOS")
        STRING(REGEX MATCH "release ([0-9]+\\.[0-9]+)" CENTOS "${LINUX_ISSUE}")
        SET(LINUX_NAME "CentOS_${CMAKE_MATCH_1}")
        SET(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "CentOS")
      # Ubuntu case
      if(LINUX_ISSUE MATCHES "Ubuntu")
        STRING(REGEX MATCH "buntu ([0-9]+\\.[0-9]+)" UBUNTU "${LINUX_ISSUE}")
        SET(LINUX_NAME "Ubuntu_${CMAKE_MATCH_1}")
        SET(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Ubuntu")
      # Debian case
      if(LINUX_ISSUE MATCHES "Debian")
        STRING(REGEX MATCH "Debian .*ux ([a-zA-Z]*/?[a-zA-Z]*) .*" DEBIAN "${LINUX_ISSUE}")
        SET(LINUX_NAME "Debian_${CMAKE_MATCH_1}")
        STRING(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        SET(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Debian")
      # Open SuSE case
      if(LINUX_ISSUE MATCHES "SUSE")
        STRING(REGEX MATCH "SUSE  ([0-9]+\\.[0-9]+)" SUSE "${LINUX_ISSUE}")
        SET(LINUX_NAME "openSUSE_${CMAKE_MATCH_1}")
        STRING(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        SET(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "SUSE")
    endif(DEFINED LINUX_ISSUE)
  endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif(UNIX)

# PACKAGING OPTIONS: DEB
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "furylynx")
# autogenerate dependency information
SET (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# PACKAGING OPTIONS: RPM
SET(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 license")
SET(CPACK_RPM_PACKAGE_VENDOR "furylynx")
SET(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
SET(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION /usr/local /usr/local/share /usr/local/lib)
SET(CPACK_RPM_PACKAGE_REQUIRES "${MYLIB_REQUIRES_RPM}")
SET(CPACK_RPM_PACKAGE_AUTOREQ "no")
#SET(CPACK_RPM_PACKAGE_RELOCATABLE FALSE)


INCLUDE(CPack)
