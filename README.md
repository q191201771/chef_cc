chef
====
### Brief
* <B>chef_base</B> is a set of linux c++ tools(log,buffer,thread,etc).
* <B>chef_io</B> is a multi-thread epoll lib, <B>io_tcp.h</B> is the unique interface header<br>
  and you can get more user-manual in it.

### Dependings
1. <B>boost</B><br>
  $sudo apt-get install libboost-dev libboost-all-dev -y<br>
  (i've tested 1.53 & 1.55)
2. <B>cmake</B><br>
  $sudo apt-get install cmake -y
3. <B>c++11</B>(now gcc contain it already)
4. <B>google protobuf</B>(optional, to build demo_chat)<br>
  $sudo apt-get install protobuf-compiler libprotobuf-dev -y

### Build
* <br>
  $./build.sh

* <B>result</B><br>
    libchefbase.so libchefio.so in ./lib/ <br>
    test&example in ./bin/

