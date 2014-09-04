#!/bin/bash

cd bin
rm *.log.chef valg
./atomic_test
./buffer_test
./condition_test
./mutex_test
./noncopyable_test
./rwlock_test
./thread_test
./wait_event_test
./chunk_head_test
./async_log_test
./thread_pool_test
./current_proc_test
./current_thd_test
./uuid_test
./spin_lock_test
