#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(bicon,0.11)
AC_CONFIG_SRCDIR([bjoining/bjoining_charprop.c])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])
AC_CHECK_LIB([util], [forkpty])

PKG_CHECK_MODULES(FRIBIDI,fribidi >= 0.10.4)
AC_SUBST(FRIBIDI_LIBS)
AC_SUBST(FRIBIDI_CFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([paths.h stdlib.h string.h sys/file.h sys/ioctl.h sys/time.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_WAIT3
AC_CHECK_FUNCS([dup2 memmove memset putenv select strrchr])

AC_CONFIG_FILES([bicon.pc
                 Makefile
                 bconsole/Makefile
                 bjoining/Makefile
                 bicon/Makefile
                 keymap/Makefile
                 font/Makefile])
AC_OUTPUT
