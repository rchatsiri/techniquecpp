# Install script for directory: /home/chatsiri/workspacecpp/techniquecpp/pthread_queue

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesConfig.cmake;/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesConfigVersion.cmake")
FILE(INSTALL DESTINATION "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build" TYPE FILE FILES
    "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/CMakeFiles/QueueProcessesConfig.cmake"
    "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/QueueProcessesConfigVersion.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  IF(EXISTS "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake"
         "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/CMakeFiles/Export/_home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake")
FILE(INSTALL DESTINATION "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build" TYPE FILE FILES "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/CMakeFiles/Export/_home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
     "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets-noconfig.cmake")
FILE(INSTALL DESTINATION "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build" TYPE FILE FILES "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/CMakeFiles/Export/_home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/QueueProcessesTargets-noconfig.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/src/cmake_install.cmake")
  INCLUDE("/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/unit_test/cmake_install.cmake")
  INCLUDE("/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/src/mqueue/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
