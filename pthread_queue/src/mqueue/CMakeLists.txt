CONFIGURE_FILE(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

ADD_LIBRARY(mqueue SHARED mqueue.cpp mqueue.hpp config.h.in)

SET_TARGET_PROPERTIES(mqueue PROPERTIES PUBLIC_HEADER "mqueue.hpp;${CMAKE_CURRENT_BINARY_DIR}/config.h")

SET( apr_SOURCE_DIR /home/chatsiri/workspacecpp/apr-1.4.8/build_linux/include/apr-1)
SET( apr_LIBRARY_DIR /home/chatsiri/workspacecpp/apr-1.4.8/build_linux/lib )


SET( LIBS ${LIBS} ${apr_LIBRARY_DIR} )
#Boost included path , include library.
INCLUDE_DIRECTORIES(${apr_SOURCE_DIR})
#

INSTALL(TARGETS mqueue
        EXPORT  QueueProcessesTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/mqueue"
			  COMPONENT dev)
       
