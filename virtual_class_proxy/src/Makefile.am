# Make src file 
# libarries for scann
lib_LTLIBRARIES = libsharedutil.la
# Scanner types, Algorithm types
libsharedutil_la_SOURCES = shared_util.hpp 
# program binary file
bin_PROGRAMS  = sharedutil 

# source file.
sharedutil_SOURCES = main.cpp   


# name of libarries
sharedutil_LDADD    = $(top_builddir)/src/libsharedutil.la  
#contain source file directory
sharedutil_CPPFLAGS = -I/home/chatsiri/workspacecpp/boost-truck/include -I/opt/AMDAPP/include -I/home/chatsiri/workspacecpp/gtest-1.6.0/include -I/home/chatsiri/workspacecpp/google-coredumper-read-only/build/include 

AM_CXXFLAGS   = -g3 -O0

