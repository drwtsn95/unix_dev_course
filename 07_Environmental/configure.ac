#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [support@rhasher.xyz])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([missing rhash lib])])
AC_CHECK_LIB([readline],[readline],[],[])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_ARG_ENABLE([readline], AS_HELP_STRING([--enable-readline], [use readline, not getline]), AC_DEFINE(USE_READLINE, [1], [Readline mode]), [use_readline="false"])
AS_IF([test "x$use_readline" = "xfalse"], [AC_SUBST(LIBS, ["-lrhash"])])

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
