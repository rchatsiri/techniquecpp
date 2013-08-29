# Details
# MQUEUE top level directory : single source.
# src : source file
# unit_test : google unit_test

cmake_minimum_required(VERSION 2.8)

# Project name : Distributed File System.
PROJECT(mqueue)

set(MQUEUE_MAJOR_VERSION 0)
set(MQUEUE_MINOR_VERSION 1)
set(MQUEUE_PATCH_VERSION 0)
set(MQUEUE_VERSION
${MQUEUE_MAJOR_VERSION}.${MQUEUE_MINOR_VERSION}.${MQUEUE_PATCH_VERSION})

set(DEF_INSTALL_CMAKE_DIR /home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build)


set(INSTALL_LIB_DIR "${DEF_INSTALL_CMAKE_DIR}/lib" CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR "${DEF_INSTALL_CMAKE_DIR}/bin" CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR "${DEF_INSTALL_CMAKE_DIR}/include" CACHE PATH
    "Installation directory for header files")

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
    "Installation directory for CMake files")


foreach(p LIB BIN INCLUDE CMAKE)
set(var INSTALL_${p}_DIR)
if(NOT IS_ABSOLUTE "${${var}}")
	set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
 endif()
endforeach()

INCLUDE_DIRECTORIES(
"${PROJECT_SOURCE_DIR}"
"${PROJECT_BINARY_DIR}"
)


#Top directory
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(unit_test)
ADD_SUBDIRECTORY(src/mqueue)

EXPORT(TARGETS mqueue queue_processes
       FILE "${PROJECT_BINARY_DIR}/QueueProcessesTargets.cmake")

EXPORT(PACKAGE  queue_processes)

FILE(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"  "${INSTALL_INCLUDE_DIR}")
# build file
SET(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
CONFIGURE_FILE(QueueProcessesConfig.cmake.in "${PROJECT_BINARY_DIR}/QueueProcessesConfig.cmake" @ONLY)
# install
SET(CONF_INCLUDE_DIR  "{PROJECT_SOURCE_DIR}" "{PROJECT_BINARY_DIR}")
CONFIGURE_FILE(QueueProcessesConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QueueProcessesConfig.cmake" @ONLY)
# both
CONFIGURE_FILE(QueueProcessesConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/QueueProcessesConfigVersion.cmake" @ONLY)


INSTALL(FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QueueProcessesConfig.cmake"
              "${PROJECT_BINARY_DIR}/QueueProcessesConfigVersion.cmake"
              DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

INSTALL(EXPORT QueueProcessesTargets DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

#set top level
SET( hpcncdfs_SOURCE /home/chatsiri/workspacecpp/techniquecpp/pthread_queue/src/queue_processes.cpp )
SET( hpcncdfs_BIN_DIR /home/chatsiri/workspacecpp/techniquecpp/pthread_queue/bin)

#Boost library path, 3rd library
SET( boost_SOURCE_DIR /home/chatsiri/workspacecpp/boost-truck)
SET( boost_LIBRARY_DIR /home/chatsiri/workspacecpp/boost-truck/stage/lib)

SET( LIBS ${LIBS} ${boost_LIBRARY_DIR})
#Boost included path , include library.
INCLUDE_DIRECTORIES(${boost_SOURCE_DIR})
#FIND_LIBRARY(${boost_LIBRARY_DIR})

#APR Apache library.
#INCLUDE_DIRECTORIES(${apr_SOURCE_DIR})
#SET( LIBS ${LIBS} ${apr_LIBRARY_DIR} )
