# Make src file 
# libarries for scann
lib_LTLIBRARIES = libtire.la
# Scanner types, Algorithm types
libtire_la_SOURCES = tire.hpp
# program binary file
bin_PROGRAMS  = tire

# source file.
tire_SOURCES = main.cpp


# name of libarries
tire_LDADD    = $(top_builddir)/src/libtire.la  
#contain source file directory
tire_CPPFLAGS = -I/home/chatsiri/workspacecpp/techniquecpp/dfs/src -I/home/chatsiri/workspacecpp/boost-truck/include -I/usr/include/ -I/home/chatsiri/workspacecpp/gtest-1.6.0/include -I/home/chatsiri/workspacecpp/google-coredumper-read-only/build/include

AM_CXXFLAGS   = -g3 -O0

