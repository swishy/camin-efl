m4_define([v_maj], [0])
m4_define([v_min], [0])
m4_define([v_mic], [1])
m4_define([project_version], [v_maj.v_min.v_mic])

m4_define([lt_cur], m4_eval(v_maj + v_min))
m4_define([lt_rev], v_mic)
m4_define([lt_age], v_min)

AC_INIT([CAmin], [project_version], [swishyTM@gmail.com])
LT_INIT
AC_CONFIG_SRCDIR(configure.ac)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(1.6 dist-bzip2 [subdir-objects])


define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl

AC_PROG_LIBTOOL

version_info="lt_cur:lt_rev:lt_age"
AC_SUBST([version_info])

# Compiler
AC_PROG_CC

# pkg-config
PKG_PROG_PKG_CONFIG

AC_DEFINE([EFL_BETA_API_SUPPORT], [1], [Enable access to unstable EFL API thats still in beta])

PKG_CHECK_MODULES(ECORE, [ ecore-con ecore ], [have_ecore="yes"], [have_ecore="no"])

PKG_CHECK_MODULES([EINA], [eina], [have_eina="yes"], [have_eina="no"])

PKG_CHECK_MODULES([EO], [eo], [have_eo="yes"], [have_eo="no"])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([
Makefile
])

AC_OUTPUT

echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE_NAME $PACKAGE_VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo
echo " ecore.........: ${have_ecore}"
echo " eina..........: ${have_eina}"
echo " eo............: ${have_eo}"
echo
