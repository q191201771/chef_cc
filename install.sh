if [ -d /usr/include/chef ]; then
    :
else
    mkdir -p /usr/include/chef
fi

cp chef_base/*.h /usr/include/chef/
cp chef_io/io_tcp.h /usr/include/chef/
cp lib/libchefbase.so lib/libchefio.so /usr/lib/
