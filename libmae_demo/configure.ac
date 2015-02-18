AC_INIT([libmae-demo], [0.9.0])

AM_INIT_AUTOMAKE([subdir-objects])

# Use .cpp as default extension if no _SOURCES have been defined
#AM_DEFAULT_SOURCE_EXT = .cpp

#required packages
PKG_CHECK_MODULES(LIBMAE, libmae >= 0.9.0)
AC_SUBST(LIBMAE_CFLAGS)
AC_SUBST(LIBMAE_LIBS)

PKG_CHECK_MODULES(SDL, sdl2 >= 2.0.2)
AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

PKG_CHECK_MODULES(SDLIMAGE, SDL2_image)
AC_SUBST(SDLIMAGE_CFLAGS)
AC_SUBST(SDLIMAGE_LIBS)

PKG_CHECK_MODULES(SDLTTF, SDL2_ttf)
AC_SUBST(SDLTTF_CFLAGS)
AC_SUBST(SDLTTF_LIBS)

#we have c++ code
AC_PROG_CXX

#c++11 setup
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

#initialize lt - create a .so file in the end
LT_INIT

AC_CONFIG_FILES([libmae_demo.pc Makefile include/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AC_OUTPUT
