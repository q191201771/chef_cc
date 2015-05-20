# chef_cc

====

## Brief

* **chef_base** is a set of linux c++ tools(log,buffer,thread,etc).

* **chef_io** is a multi-thread epoll lib, **io_tcp.h** is the unique interface header and you can get more user-manual in it.

## Dependings

### boost

```
$sudo apt-get install libboost-dev libboost-all-dev -y
```  

(i've tested 1.53 & 1.55)

### cmake

```
$sudo apt-get install cmake -y
```

### c++11(now gcc contain it already)

### google protobuf(optional, to build demo_chat)

```
$sudo apt-get install protobuf-compiler libprotobuf-dev -y
```

## Build

```
$./build.sh
```

### result

libchefbase.so libchefio.so in ./lib/

test&example in ./bin/

