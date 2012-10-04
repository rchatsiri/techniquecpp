# Make src file 
# libarries for scann
lib_LTLIBRARIES = libscanner.la
# Scanner types, Algorithm types
libscanner_la_SOURCES = scanner.cpp trie.hpp utils/clutil_momory.hpp 
# program binary file
bin_PROGRAMS  = scanner

# source file.
scanner_SOURCES = main.cpp trie.cpp  


# name of libarries
scanner_LDADD    = $(top_builddir)/src/libscanner.la  
#contain source file directory
scanner_CPPFLAGS = -I/home/chatsiri/workspacecpp/techniquecpp/trie_class/src -I/home/chatsiri/workspacecpp/boost-truck/include -I/usr/include/ -I/home/chatsiri/workspacecpp/gtest-1.6.0/include -I/home/chatsiri/workspacecpp/google-coredumper-read-only/build/include -I/home/chatsiri/workspacecpp/techniquecpp/trie_class/src/utils -I/home/chatsiri/workspacecpp/techniquecpp/trie_class/src/utils/config -I-I/home/chatsiri/workspacecpp/techniquecpp/trie_class/src/utils/logger

# -library boost_program_options
# -lOpenCL 
# -  -Iboost_program_options -IOpenCL
AM_CXXFLAGS   = -g3 -O0

