
GET_FILENAME_COMPONENT(QUEUEPROCESSES_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
SET(QUEUEPROCESSES_INCLUDE_DIRS "/home/chatsiri/workspacecpp/techniquecpp/pthread_queue;/home/chatsiri/workspacecpp/techniquecpp/pthread_queue")


include("${QUEUEPROCESSES_CMAKE_DIR}/QueueProcessesTargets.cmake")


SET(QUEUEPROCESSES_LIBRARIES  libdfs)
SET(QUEUEPROCESSES_EXECUTABLE dfs_processes)
