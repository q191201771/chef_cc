<pre>
@dependence
  1. boost
    $sudo apt-get install liboost1.53-dev -y
    $sudo apt-get install liboost1.53-all-dev -y
  2. cmake
    $sudo apt-get install cmake -y
  3. c++11(now gcc version will contain it)

@build
  $cd build
  $cmake . && make

  @build out:
    libchefbase.a libchefio.a in chef/lib/
    test&example in chef/bin/

@brief
  @the only io interface header: chef_io/io_tcp.h
   and you can get more user-manual in it

  @wanna use gcc to build your own io-server with chef?
    1. build chefio chefbase(follow the above operation)
    2. use test_chef_io/test_srv.cc for demonstration
      $cd test_chef_io
      $g++ test_srv.cc -I../chef_io -I../chef_base -std=c++11 -L../lib -lchefio -lchefbase -lboost_thread -lboost_system -lboost_date_time -o test_srv
      $./test_srv

  @chef_base is an linux c++ base lib,i pefer boost now.
</pre>
