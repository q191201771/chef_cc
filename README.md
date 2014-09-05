chef
====
An usability multi-thread epoll lib

### Dependings
1. boost<br>
  $sudo apt-get install libboost-dev libboost-all-dev -y<br>
  (i've tested 1.53 & 1.55)
2. cmake<br>
  $sudo apt-get install cmake -y
3. c++11(now gcc contain it already)
4. google protobuf(optional, to demo_chat)<br>
  $sudo apt-get install protobuf-compiler libprotobuf-dev -y

### Build
* <br>
  $cd build<br>
  $cmake . && make<br>
  or just<br>
  $./build.sh (will build all chefbase unittest)

* build out:<br>
    libchefbase.so libchefio.so in chef/lib/ <br>
    test&example in chef/bin/

### Brief
* the unique interface of chef_io: chef_io/io_tcp.h <br>
 and you can get more user-manual in it

* build your own server with chef? 
 1. build chefio chefbase(follow the above operation)
 2. use test_chef_io/test_srv.cc for demonstration <br>
   $cd lib <br>
   $cp ../test_chef_io/test_srv.cc . <br>
   $g++ test_srv.cc -I../chef_io -I../chef_base -std=c++11 -L../lib -lchefio -lchefbase -lboost_thread -lboost_system -lboost_date_time -lboost_chrono -o test_srv <br>
   $./test_srv 

* chef_base is a set of linux c++ tool,nowadays i pefer boost.

