CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
INCLUDE_DIRECTORIES(${ROOT_DIR}/chef_base ${ROOT_DIR}/test_chef_base)
ADD_EXECUTABLE(memprint ${ROOT_DIR}/test_chef_base/memprint.cc)
TARGET_LINK_LIBRARIES(memprint chefbase pthread)

ADD_EXECUTABLE(buffer_test ${ROOT_DIR}/test_chef_base/buffer_test.cc)
TARGET_LINK_LIBRARIES(buffer_test chefbase pthread)

ADD_EXECUTABLE(rwlock_test ${ROOT_DIR}/test_chef_base/rwlock_test.cc)
TARGET_LINK_LIBRARIES(rwlock_test chefbase pthread)

ADD_EXECUTABLE(log_test ${ROOT_DIR}/test_chef_base/log_test.cc)
TARGET_LINK_LIBRARIES(log_test chefbase pthread)

ADD_EXECUTABLE(thread_test ${ROOT_DIR}/test_chef_base/thread_test.cc)
TARGET_LINK_LIBRARIES(thread_test chefbase pthread)

ADD_EXECUTABLE(task_thread_test ${ROOT_DIR}/test_chef_base/task_thread_test.cc)
TARGET_LINK_LIBRARIES(task_thread_test chefbase pthread)
