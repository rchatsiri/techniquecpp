ADD_EXECUTABLE(queue_processes queue_processes.cpp)

TARGET_LINK_LIBRARIES(queue_processes mqueue)

INSTALL(TARGETS queue_processes
        EXPORT  QueueProcessesTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

