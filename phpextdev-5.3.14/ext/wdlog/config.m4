dnl $Id$
dnl config.m4 for extension wdlog

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(wdlog, for wdlog support,
dnl Make sure that the comment is aligned:
dnl [  --with-wdlog             Include wdlog support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(wdlog, whether to enable wdlog support,
dnl Make sure that the comment is aligned:
[  --enable-wdlog           Enable wdlog support])

if test "$PHP_WDLOG" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-wdlog -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/wdlog.h"  # you most likely want to change this
  dnl if test -r $PHP_WDLOG/$SEARCH_FOR; then # path given as parameter
  dnl   WDLOG_DIR=$PHP_WDLOG
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for wdlog files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WDLOG_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WDLOG_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the wdlog distribution])
  dnl fi

  dnl # --with-wdlog -> add include path
  dnl PHP_ADD_INCLUDE($WDLOG_DIR/include)

  dnl # --with-wdlog -> check for lib and symbol presence
  dnl LIBNAME=wdlog # you may want to change this
  dnl LIBSYMBOL=wdlog # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WDLOG_DIR/lib, WDLOG_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_WDLOGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong wdlog lib version or lib not found])
  dnl ],[
  dnl   -L$WDLOG_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(WDLOG_SHARED_LIBADD)

  PHP_NEW_EXTENSION(wdlog, wdlog.c, $ext_shared)
fi
