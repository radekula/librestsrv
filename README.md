# librestsrv

### Description ###
Librestsrv is a custom library written in C/C++ for handling REST requests. Its purpose is to be as small, simple and versatile as possible. Features like caching, binary data transfer, html server are not planned. The plan is to keep code simple.
New functionalities and features will be added mostly when needed.

As for now this is more a 'proof of concept' project or 'work in progress' project - not ready for production systems!.

### Characteristic ###
 * Custom socket managment - no need for external libriaries
 * Only one type of request supported - REST
 * Uses jsoncpp
 * Multithreaded
 * Modern C++ features

### Build ###
```
cd librestsrv
mkdir -p build && cd build
cmake ..
make
```

### Usage ###
See examples.

### TODO ###
 * Responses for requests
 * Threads pool for connections
 * Support for content-type
 * Return other than REST request back to main program
 * Propper tests
