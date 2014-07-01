SET(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
INCLUDE_DIRECTORIES(${ROOT_DIR}/chef_base ${ROOT_DIR}/chef_io ${ROOT_DIR}/chat/)

ADD_EXECUTABLE(chat_srv 
    ${ROOT_DIR}/chat/chat_srv.cc
    ${ROOT_DIR}/chat/chunk.cc)
TARGET_LINK_LIBRARIES(chat_srv chefio chefbase pthread)

ADD_EXECUTABLE(chat_cli
    ${ROOT_DIR}/chat/chat_cli.cc
    ${ROOT_DIR}/chat/chunk.cc
    ${ROOT_DIR}/chat/chat.pb.cc)
TARGET_LINK_LIBRARIES(chat_cli chefio chefbase pthread libprotobuf.a)
