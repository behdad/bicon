##############################################################################
## $Id$
## $Auther: behdad $
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Autoconf -*-
## Process this file with autoconf to produce a configure script.
## Use autoupdate to update this file for newer versions of autoconf.
## Use autoscan to check if you need to add something to this file.

AC_PREREQ(2.59)
AC_INIT([BiCon],[0.1.pre],[http://bugs.arabeyes.org/cgi-bin/bugzilla/enter_bug.cgi?product=BiCon])
AC_REVISION([$Id$])
AC_CONFIG_SRCDIR(bicon/bicon.c)
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([gnu check-news])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S

# Checks for libraries.
AC_CHECK_LIB(dl, dlopen)
AC_CHECK_LIB(util, forkpty)

PKG_CHECK_MODULES(FRIBIDI,fribidi >= 0.10.4)
AC_SUBST(FRIBIDI_LIBS)
AC_SUBST(FRIBIDI_CFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_TIME
AC_CHECK_HEADERS([sys/types.h sys/stat.h stdlib.h string.h strings.h inttypes.h unistd.h])
AC_CHECK_HEADERS([paths.h sys/file.h sys/ioctl.h termios.h])

# Checks for typedefs and structures.
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for compiler characteristics.
changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall " ;;
  esac
  case " $CFLAGS " in
  *[\ \	]-pedantic[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -pedantic " ;;
  esac
fi
changequote([,])dnl

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_STAT
AC_CHECK_FUNCS([dup2 memmove memset putenv select])
AC_TYPE_SIGNAL

# Generate output
AC_CONFIG_FILES([bicon.pc
                 Makefile
                 bconsole/Makefile
                 bicon/Makefile
                 bin/Makefile
                 bjoining/Makefile
                 doc/Makefile
                 doc/man/Makefile
                 font/Makefile
                 keymap/Makefile
		 testtext/Makefile])
dnl AC_CONFIG_FILES([bin/bicon], [chmod +x bin/bicon])
AC_OUTPUT
