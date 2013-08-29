# Install script for directory: /home/chatsiri/workspacecpp/techniquecpp/pthread_queue/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "bin")
  IF(EXISTS "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes")
FILE(INSTALL DESTINATION "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin" TYPE EXECUTABLE FILES "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/src/queue_processes")
  IF(EXISTS "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "bin")

