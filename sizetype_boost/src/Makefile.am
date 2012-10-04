# Make src file 
# libarries for scann
lib_LTLIBRARIES = libtypeboost.la

# Scanner types, Algorithm types
libtypeboost_la_SOURCES = typeboosttest.hpp 

# program binary file
bin_PROGRAMS  = typeboost

# source file.
typeboost_SOURCES = main.cpp  


# name of libarries
typeboost_LDADD    = $(top_builddir)/src/libtypeboost.la  
#contain source file directory
typeboost_CPPFLAGS = -I/home/chatsiri/workspacecpp/boost-truck/include -I/home/chatsiri/workspacecpp/gtest-1.6.0/include 

AM_CXXFLAGS   = -g3 -O0

