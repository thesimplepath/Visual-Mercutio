dnl @synopsis AC_CXX_TEMPLATE_KEYWORD_QUALIFIER
dnl
dnl If the compiler supports use of the template keyword as a qualifier,
dnl define HAVE_TEMPLATE_KEYWORD_QUALIFIER.
dnl
dnl @version $Id: ac_cxx_template_keyword_qualifier.m4,v 1.1 2001/11/12 07:48:22 dcrowley Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN([AC_CXX_TEMPLATE_KEYWORD_QUALIFIER],
[AC_CACHE_CHECK(whether the compiler supports use of the template keyword as a qualifier,
ac_cv_cxx_template_keyword_qualifier,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([
class A { public : A() {}; template<class T> static T convert() { return T(); }
};
],[double z = A::template convert<double>(); return 0;],
 ac_cv_cxx_template_keyword_qualifier=yes, ac_cv_cxx_template_keyword_qualifier=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_template_keyword_qualifier" = yes; then
  AC_DEFINE(HAVE_TEMPLATE_KEYWORD_QUALIFIER,,
            [define if the compiler supports use of the template keyword as a qualifier])
fi
])
