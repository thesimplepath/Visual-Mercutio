dnl @synopsis PETI_WITH_DMALLOC
dnl
dnl The dmalloc library is an useful tool to debug memory problems in
dnl your programs, but you don't really want to compile
dnl dmalloc-support into every binary you produce, because dmalloc
dnl brings performance loss.
dnl
dnl The PETI_WITH_DMALLOC macro defines a user switch '--with-dmalloc'
dnl which can be used likes this:
dnl
dnl      ./configure --with-dmalloc[=BASE-PATH]
dnl
dnl If no BASE-PATH has been provided, "/usr/local" will be used as
dnl default.
dnl
dnl The BASE-PATH is the place where autoconf expects to find the
dnl include- and link library files of dmalloc, specifically in:
dnl
dnl      $(BASE-PATH)/include
dnl      $(BASE-PATH)/lib
dnl
dnl If dmalloc-support has been enabled, the pre-processor defines
dnl "DEBUG_DMALLOC" and "DMALLOC_FUNC_CHECK" will added to CPPFLAGS
dnl as well as the apropriate "-I" statement.
dnl
dnl Use the first define in your source codes to determine whether you
dnl have dmalloc support enabled or not. Usually something like this
dnl will suffice:
dnl
dnl      #ifdef DEBUG_DMALLOC
dnl      #  include <dmalloc.h>
dnl      #endif
dnl
dnl You will find dmalloc at <http://www.dmalloc.com/>.
dnl
dnl @version $Id: peti_with_dmalloc.m4,v 1.1 2001/11/21 06:07:25 dcrowley Exp $
dnl @author Peter Simons <simons@computer.org>
dnl
AC_DEFUN([PETI_WITH_DMALLOC], [
AC_MSG_CHECKING(whether to use dmalloc library)
AC_ARG_WITH(dmalloc,
[  --with-dmalloc[=ARG]     Compile with dmalloc library],
if test "$withval" = "" -o "$withval" = "yes"; then
    ac_cv_dmalloc="/usr/local"
else
    ac_cv_dmalloc="$withval"
fi
AC_MSG_RESULT(yes)
CPPFLAGS="$CPPFLAGS -DDEBUG_DMALLOC -DDMALLOC_FUNC_CHECK -I$ac_cv_dmalloc/include"
LDFLAGS="$LDFLAGS -L$ac_cv_dmalloc/lib"
LIBS="$LIBS -ldmalloc"
,AC_MSG_RESULT(no))
])
