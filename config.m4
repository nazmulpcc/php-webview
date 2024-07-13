dnl config.m4 for extension webview

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([webview],
dnl   [for webview support],
dnl   [AS_HELP_STRING([--with-webview],
dnl     [Include webview support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([webview],
  [whether to enable webview support],
  [AS_HELP_STRING([--enable-webview],
    [Enable webview support])],
  [no])

if test "$PHP_WEBVIEW" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, WEBVIEW_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-webview -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/webview.h"  # you most likely want to change this
  dnl if test -r $PHP_WEBVIEW/$SEARCH_FOR; then # path given as parameter
  dnl   WEBVIEW_DIR=$PHP_WEBVIEW
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for webview files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WEBVIEW_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WEBVIEW_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the webview distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-webview -> add include path
  dnl PHP_ADD_INCLUDE($WEBVIEW_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-webview -> check for lib and symbol presence
  LIBNAME=webview # you may want to change this
  LIBSYMBOL=webview_create # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_WEBVIEW_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your webview library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WEBVIEW_DIR/$PHP_LIBDIR, WEBVIEW_SHARED_LIBADD)
    AC_DEFINE(HAVE_WEBVIEW_FEATURE, 1, [ ])
  ],[
    AC_MSG_ERROR([FEATURE not supported by your webview library.])
  ],[
    -L$WEBVIEW_DIR/$PHP_LIBDIR -lm
  ])
  PHP_SUBST(WEBVIEW_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_WEBVIEW, 1, [ Have webview support ])

  PHP_NEW_EXTENSION(webview, webview.c, $ext_shared)
fi
