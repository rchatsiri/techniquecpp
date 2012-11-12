AC_PREREQ([2.59])
AC_INIT([cpp_concept],[0.1],[technique@hnmav.org])

#unique source file 
AC_CONFIG_SRCDIR([src/main.cpp])

#extra script build
AC_CONFIG_AUX_DIR([build-aux])

#build flags
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

#check for program
#AC_PROG_CC([gcc])
AC_PROG_CXX([g++])

#libtools
m4_pattern_allow([AC_PROG_LIBTOOL])
AC_PROG_LIBTOOL

##################################
##   Libraries declare path     ##
##################################
LIBS  ="-boost_program_options $LIBS"

#check for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

#check library function
AC_FUNC_MALLOC

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
								 src/Makefile])
#output file
AC_OUTPUT

