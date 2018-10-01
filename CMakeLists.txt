cmake_minimum_required (VERSION 3.0)
project (librestsrv)

set (restsrv_VERSION_MAJOR 0)
set (restsrv_VERSION_MINOR 1)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.0)
    if (NOT DEFINED CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 14)
    endif ()
else ()
    set (CMAKE_CXX_FLAGS "-std=c++14")
endif ()

set (BUILD_DIR "build")

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(${JSONCPP_INCLUDE_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})
link_libraries(${JSONCPP_LIBRARIES})

include_directories (${CMAKE_CURRENT_LIST_DIR}/include)
include_directories (${CMAKE_CURRENT_LIST_DIR}/include/client)
include_directories (${CMAKE_CURRENT_LIST_DIR}/include/error)
include_directories (${CMAKE_CURRENT_LIST_DIR}/include/global)
include_directories (${CMAKE_CURRENT_LIST_DIR}/include/log)
include_directories (${CMAKE_CURRENT_LIST_DIR}/include/server)

file (GLOB LIB_RESTSRV_SRC "src/client/*.cxx" "src/log/*.cxx" "src/server/*.cxx")

add_library (restsrv SHARED ${LIB_RESTSRV_SRC})
add_library (restsrv_static STATIC ${LIB_RESTSRV_SRC})
