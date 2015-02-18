#!/bin/bash

AC_INIT([libmae_eventing], [0.9.0])

AM_INIT_AUTOMAKE([subdir-objects])

# Use .cpp as default extension if no _SOURCES have been defined

#required packages
PKG_CHECK_MODULES(LIBMAE, libmae >= 0.9.0)
AC_SUBST(LIBMAE_CFLAGS)
AC_SUBST(LIBMAE_LIBS)

#PKG_CHECK_MODULES([LIBXMLXX], [libxml++-2.6])
PKG_CHECK_MODULES(LIBXMLXX, libxml++-2.6 >= 2.6)
AC_SUBST(LIBXMLXX_CFLAGS)
AC_SUBST(LIBXMLXX_LIBS)

AX_BOOST_BASE([1.53])
AX_BOOST_ASIO([1.53])

#we have c++ code
AC_PROG_CXX

#c++11 setup
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

#initialize lt - create a .so file in the end
LT_INIT

AC_CONFIG_FILES([libmae_eventing.pc Makefile include/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AC_OUTPUT
