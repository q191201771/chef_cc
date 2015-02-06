#!/bin/bash

cd ./bin
rm -rf `ls | grep -v 'cfg.*'`
cd ..
rm -rf *.log.chef log lib
rm -rf `find . -name 'CMakeCache.txt'`
rm -rf `find . -name 'CMakeFiles'`
rm -rf `find ./build -name 'Makefile'`
rm -rf `find . -name 'cmake_install.cmake'`
