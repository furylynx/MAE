AC_INIT([libmae], [0.9.0])

AM_INIT_AUTOMAKE([subdir-objects])

# Use .cpp as default extension if no _SOURCES have been defined
#AM_DEFAULT_SOURCE_EXT = .cpp

#JNI setup
#AX_PROG_JAVAH
AX_JNI_INCLUDE_DIR

for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS
do
   	CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR"

	#handle glitch in the matrix...
	if [ test -d "$JNI_INCLUDE_DIR/linux" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/linux"
	elif [ test -d "$JNI_INCLUDE_DIR/win32" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/win32"
	elif [ test -d "$JNI_INCLUDE_DIR/genunix" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/genunix"
	elif [ test -d "$JNI_INCLUDE_DIR/bsdos" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/bsdos"
	elif [ test -d "$JNI_INCLUDE_DIR/freebsd" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/freebsd"
	elif [ test -d "$JNI_INCLUDE_DIR/darwin" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/darwin"
	elif [ test -d "$JNI_INCLUDE_DIR/alpha" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/alpha"
	elif [ test -d "$JNI_INCLUDE_DIR/solaris" ]; then
		CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR/solaris"
	fi
done

#required packages
PKG_CHECK_MODULES(OPENCV, opencv >= 2.4.8)
AC_SUBST(OPENCV_CFLAGS)
AC_SUBST(OPENCV_LIBS)

#PKG_CHECK_MODULES([LIBXMLXX], [libxml++-2.6])
PKG_CHECK_MODULES(LIBXMLXX, libxml++-2.6 >= 2.6)
AC_SUBST(LIBXMLXX_CFLAGS)
AC_SUBST(LIBXMLXX_LIBS)

#we have c++ code
AC_PROG_CXX

#c++11 setup
AX_CXX_COMPILE_STDCXX_11(noext,mandatory)
#AX_CXX_COMPILE_STDCXX_11()

#initialize lt - create a .so file in the end
LT_INIT

AC_CONFIG_FILES([libmae.pc Makefile include/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AC_OUTPUT
