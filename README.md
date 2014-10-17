chef
====
### Brief
* chef_base is a set of linux c++ tools
* chef_io is a multi-thread epoll lib, io_tcp.h is the unique interface header<br>
  and you can get more user-manual in it

### Dependings
1. boost<br>
  $sudo apt-get install libboost-dev libboost-all-dev -y<br>
  (i've tested 1.53 & 1.55)
2. cmake<br>
  $sudo apt-get install cmake -y
3. c++11(now gcc contain it already)
4. google protobuf(optional, to build demo_chat)<br>
  $sudo apt-get install protobuf-compiler libprotobuf-dev -y

### Build
* <br>
  ./build.sh

* result:<br>
    libchefbase.so libchefio.so in ./chef/lib/ <br>
    test&example in ./chef/bin/

