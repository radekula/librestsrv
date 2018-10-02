#!/bin/bash

g++ -I../include -I../include/client -c example1.cxx -o example1.o
g++ example1.o ../build/librestsrv_static.a -ljsoncpp -o example1
./example1
