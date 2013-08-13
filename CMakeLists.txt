
cmake_minimum_required(VERSION 2.8)

set (PROJECT mchat)

PROJECT(${PROJECT})

# build project
ADD_EXECUTABLE(${PROJECT}
  ./main.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT} ${LIBRARY} m)

# test client
ADD_EXECUTABLE(client
  ./client.c
)

TARGET_LINK_LIBRARIES(client ${LIBRARY})

# test server
ADD_EXECUTABLE(server
  ./server.c
)

TARGET_LINK_LIBRARIES(server ${LIBRARY})





























