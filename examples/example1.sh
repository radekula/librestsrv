#!/bin/bash

g++ -I../include -c example1.cxx -o example1.o
g++ example1.o ../build/librestsrv_static.a  -o example1
./example1
