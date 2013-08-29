#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "queue_processes" for configuration ""
SET_PROPERTY(TARGET queue_processes APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(queue_processes PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS queue_processes )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_queue_processes "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/bin/queue_processes" )

# Import target "mqueue" for configuration ""
SET_PROPERTY(TARGET mqueue APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(mqueue PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/lib/libmqueue.so"
  IMPORTED_SONAME_NOCONFIG "libmqueue.so"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS mqueue )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_mqueue "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue/build/lib/libmqueue.so" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
