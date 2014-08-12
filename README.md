<pre>
@dependence
  1. boost
    $sudo apt-get install libboost-all-dev -y
    (i've tested 1.53 & 1.55)
  2. cmake
    $sudo apt-get install cmake -y
  3. c++11(now gcc contain it already)

@build
  $cd build
  $cmake . && make

  @build out:
    libchefbase.so libchefio.so in chef/lib/
    test&example in chef/bin/

@brief
  @the unique interface of chef_io: chef_io/io_tcp.h
   and you can get more user-manual in it

  @wanna use gcc to build your own server with chef?
    1. build chefio chefbase(follow the above operation)
    2. use test_chef_io/test_srv.cc for demonstration
      $cd lib
      $cp ../test_chef_io/test_srv.cc .
      $g++ test_srv.cc -I../chef_io -I../chef_base -std=c++11 -L../lib -lchefio -lchefbase -lboost_thread -lboost_system -lboost_date_time -lboost_chrono -o test_srv
      $./test_srv

  @chef_base is a set of linux c++ tool,nowadays i pefer boost.
</pre>
