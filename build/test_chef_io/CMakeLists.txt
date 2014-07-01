SET(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
INCLUDE_DIRECTORIES(${ROOT_DIR}/chef_base ${ROOT_DIR}/chef_io ${ROOT_DIR}/test_chef_io)

ADD_EXECUTABLE(test_srv ${ROOT_DIR}/test_chef_io/test_srv.cc)
TARGET_LINK_LIBRARIES(test_srv chefio chefbase pthread)

ADD_EXECUTABLE(pingpong_srv ${ROOT_DIR}/test_chef_io/pingpong_srv.cc)
TARGET_LINK_LIBRARIES(pingpong_srv chefio chefbase pthread)

ADD_EXECUTABLE(pingpong_cli ${ROOT_DIR}/test_chef_io/pingpong_cli.cc)
TARGET_LINK_LIBRARIES(pingpong_cli chefio chefbase pthread)

ADD_EXECUTABLE(base_srv ${ROOT_DIR}/test_chef_io/base_srv.cc)
TARGET_LINK_LIBRARIES(base_srv chefio chefbase pthread)

ADD_EXECUTABLE(lots_connect ${ROOT_DIR}/test_chef_io/lots_connect.cc)
TARGET_LINK_LIBRARIES(lots_connect chefio chefbase pthread)
