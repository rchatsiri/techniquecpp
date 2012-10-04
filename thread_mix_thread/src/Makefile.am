# Make src file 
# libarries for control threads
lib_LTLIBRARIES = libcontrolthread.la
# library
libcontrolthread_la_SOURCES = control_thread.hpp  
# program binary file
bin_PROGRAMS  = conthread

# source file.
conthread_SOURCES = main.cpp 


# name of libarries
conthread_LDADD    = $(top_builddir)/src/libcontrolthread.la  
#contain source file directory
conthread_CPPFLAGS =  -I/home/chatsiri/workspacecpp/boost-truck/include  -I/home/chatsiri/workspacecpp/gtest-1.6.0/include -I/home/chatsiri/workspacecpp/google-coredumper-read-only/build/include

# debug, optimized
AM_CXXFLAGS   = -g3 -O0

