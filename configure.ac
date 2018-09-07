AC_INIT([Thrax], [1.2.6], [help@opengrm.org])
AM_INIT_AUTOMAKE([foreign nostdinc -Wall -Werror])
AM_PROG_AR

# Thrax does not throw exceptions, so we do not generate exception handling
# code. However, users are free to re-enable exception handling.
# Thrax assumes `char` is `unsigned char`; -fsigned-char is likely unsafe.
CPPFLAGS="$CPPFLAGS -fno-exceptions -funsigned-char"
CXXFLAGS="$CXXFLAGS -std=c++11"

AC_PROG_CXX
AC_PROG_LIBTOOL
AC_DISABLE_STATIC
AC_PROG_YACC

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/lib/main/grm-manager.cc])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/include/Makefile
  src/lib/Makefile
  src/bin/Makefile
  src/grammars/Makefile
  src/utils/Makefile
])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C++])

AC_ARG_ENABLE(
  [bin],
  [AS_HELP_STRING(
    [--enable-bin],
    [enable command-line binaries])],
  [],
  [enable_bin=yes])
AM_CONDITIONAL([HAVE_BIN], [test "x$enable_bin" != xno])

AC_ARG_ENABLE(
  [readline],
  [AS_HELP_STRING(
    [--enable-readline],
    [enable readline functionality in rewrite-tester])],
  [],
  [enable_readline=no])
AM_CONDITIONAL([HAVE_READLINE], [test "x$enable_readline" != xno])

AC_CHECK_HEADER([fst/fst.h], [],
 [AC_MSG_ERROR([fst/fst.h header not found])]
)

AC_CHECK_HEADER([fst/extensions/far/far.h], [],
 [AC_MSG_ERROR([fst/extensions/far/far.h header not found])]
)

AC_CHECK_HEADER([fst/extensions/pdt/pdt.h], [],
 [AC_MSG_ERROR([fst/extensions/pdt/pdt.h header not found])]
)

AC_CHECK_HEADER([fst/extensions/mpdt/mpdt.h], [],
 [AC_MSG_ERROR([fst/extensions/mpdt/mpdt.h header not found])]
)

AC_CHECK_LIB([dl], dlopen, [DL_LIBS=-ldl])
AC_SUBST([DL_LIBS])

AC_OUTPUT
