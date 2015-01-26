#!/bin/bash

ulimit -c unlimited
rm -rf log *.log.chef
cd bin
rm *.log.chef valg core test.config.chef
./assert_test
./async_log_test
./atomic_test
./buffer_test
./chunk_head_test
./condition_test
./config_test
./current_proc_test
./current_thd_test
./daemon_test
./file_test
./mutex_test
./netstat_test
./noncopyable_test
./object_pool_test
./random_test
./rwlock_test
./singleton_test
./snippet_test
./spin_lock_test
./task_thread_test
./thread_pool_test
./thread_test
./time_test
./uuid_test
./wait_event_test
