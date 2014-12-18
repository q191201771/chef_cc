#!/bin/bash

ulimit -c unlimited
cd bin
rm *.log.chef valg core test.config.chef
./atomic_test
./async_log_test
./buffer_test
./chef_assert_test
./chunk_head_test
./condition_test
./config_test
./current_proc_test
./current_thd_test
./mutex_test
./noncopyable_test
./random_test
./rwlock_test
./spin_lock_test
./task_thread_test
./thread_pool_test
./thread_test
./uuid_test
./wait_event_test
./object_pool_test
./chef_file_test
./chef_snippet_test
