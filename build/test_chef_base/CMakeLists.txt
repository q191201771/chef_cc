CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
INCLUDE_DIRECTORIES(${ROOT_DIR}/chef_base)
ADD_EXECUTABLE(memprint_ ${ROOT_DIR}/test_chef_base/memprint_.cc)
TARGET_LINK_LIBRARIES(memprint_ chefbase)

ADD_EXECUTABLE(buffer_test ${ROOT_DIR}/test_chef_base/buffer_test.cc)
TARGET_LINK_LIBRARIES(buffer_test chefbase)

ADD_EXECUTABLE(async_log_test ${ROOT_DIR}/test_chef_base/async_log_test.cc)
TARGET_LINK_LIBRARIES(async_log_test chefbase)

ADD_EXECUTABLE(task_thread_test ${ROOT_DIR}/test_chef_base/task_thread_test.cc)
TARGET_LINK_LIBRARIES(task_thread_test chefbase)

ADD_EXECUTABLE(atomic_test ${ROOT_DIR}/test_chef_base/atomic_test.cc)
TARGET_LINK_LIBRARIES(atomic_test chefbase)

ADD_EXECUTABLE(condition_test ${ROOT_DIR}/test_chef_base/condition_test.cc)
TARGET_LINK_LIBRARIES(condition_test chefbase)

ADD_EXECUTABLE(mutex_test ${ROOT_DIR}/test_chef_base/mutex_test.cc)
TARGET_LINK_LIBRARIES(mutex_test chefbase)

ADD_EXECUTABLE(noncopyable_test ${ROOT_DIR}/test_chef_base/noncopyable_test.cc)
TARGET_LINK_LIBRARIES(noncopyable_test chefbase)

ADD_EXECUTABLE(rwlock_test ${ROOT_DIR}/test_chef_base/rwlock_test.cc)
TARGET_LINK_LIBRARIES(rwlock_test chefbase)

ADD_EXECUTABLE(thread_test ${ROOT_DIR}/test_chef_base/thread_test.cc)
TARGET_LINK_LIBRARIES(thread_test chefbase)

ADD_EXECUTABLE(wait_event_test ${ROOT_DIR}/test_chef_base/wait_event_test.cc)
TARGET_LINK_LIBRARIES(wait_event_test chefbase)

ADD_EXECUTABLE(chunk_head_test ${ROOT_DIR}/test_chef_base/chunk_head_test.cc)
TARGET_LINK_LIBRARIES(chunk_head_test chefbase)

ADD_EXECUTABLE(thread_pool_test ${ROOT_DIR}/test_chef_base/thread_pool_test.cc)
TARGET_LINK_LIBRARIES(thread_pool_test chefbase)

ADD_EXECUTABLE(current_proc_test ${ROOT_DIR}/test_chef_base/current_proc_test.cc)
TARGET_LINK_LIBRARIES(current_proc_test chefbase)

ADD_EXECUTABLE(current_thd_test ${ROOT_DIR}/test_chef_base/current_thd_test.cc)
TARGET_LINK_LIBRARIES(current_thd_test chefbase)

ADD_EXECUTABLE(uuid_test ${ROOT_DIR}/test_chef_base/uuid_test.cc)
TARGET_LINK_LIBRARIES(uuid_test chefbase)

ADD_EXECUTABLE(spin_lock_test ${ROOT_DIR}/test_chef_base/spin_lock_test.cc)
TARGET_LINK_LIBRARIES(spin_lock_test chefbase)

ADD_EXECUTABLE(random_test ${ROOT_DIR}/test_chef_base/random_test.cc)
TARGET_LINK_LIBRARIES(random_test chefbase)

ADD_EXECUTABLE(assert_test ${ROOT_DIR}/test_chef_base/assert_test.cc)
TARGET_LINK_LIBRARIES(assert_test chefbase)

ADD_EXECUTABLE(config_test ${ROOT_DIR}/test_chef_base/config_test.cc)
TARGET_LINK_LIBRARIES(config_test chefbase)

ADD_EXECUTABLE(map_test_ ${ROOT_DIR}/test_chef_base/map_test_.cc)
TARGET_LINK_LIBRARIES(map_test_ chefbase)

ADD_EXECUTABLE(daemon_test ${ROOT_DIR}/test_chef_base/daemon_test.cc)
TARGET_LINK_LIBRARIES(daemon_test chefbase)

ADD_EXECUTABLE(object_pool_test ${ROOT_DIR}/test_chef_base/object_pool_test.cc)
TARGET_LINK_LIBRARIES(object_pool_test chefbase)

ADD_EXECUTABLE(file_test ${ROOT_DIR}/test_chef_base/file_test.cc)
TARGET_LINK_LIBRARIES(file_test chefbase)

ADD_EXECUTABLE(netstat_test ${ROOT_DIR}/test_chef_base/netstat_test.cc)
TARGET_LINK_LIBRARIES(netstat_test chefbase)

ADD_EXECUTABLE(snippet_test ${ROOT_DIR}/test_chef_base/snippet_test.cc)
TARGET_LINK_LIBRARIES(snippet_test chefbase)

ADD_EXECUTABLE(singleton_test ${ROOT_DIR}/test_chef_base/singleton_test.cc)
TARGET_LINK_LIBRARIES(singleton_test chefbase)

ADD_EXECUTABLE(time_test ${ROOT_DIR}/test_chef_base/time_test.cc)
TARGET_LINK_LIBRARIES(time_test chefbase)

