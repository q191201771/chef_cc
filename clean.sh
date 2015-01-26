#!/bin/bash

rm -rf *.log.chef log bin lib
rm -rf `find . -name 'CMakeCache.txt'`
rm -rf `find . -name 'CMakeFiles'`
rm -rf `find ./build -name 'Makefile'`
rm -rf `find . -name 'cmake_install.cmake'`
