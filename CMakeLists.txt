cmake_minimum_required(VERSION 3.10)
project(hello C)

set(CMAKE_C_STANDARD 99)

add_executable(hello main.c)
add_executable(daytime daytime.c)
add_executable(daytimeserver daytimeserver.c)

add_executable(echo echo.c)
add_executable(echoserver echoserver.c)

add_executable(c c.c)
add_executable(size size.c)
add_executable(byteorder byteorder.c)

## c from android source
add_library(host SHARED
        android/libhost/copyFile.c
        android/libhost/include/host/copyFile.h)

## end c from android source

## add lsusb

add_executable(lsusb lsusb.c)

find_package(CURL REQUIRED)
message(LibCurl ${CURL_INCLUDE_PATH})
message(LibCurl ${CURL_LIBRARIES})
find_path(LIBUSB_INCLUDE_DIR
        NAMES libusb.h
        PATH_SUFFIXES "include" "libusb" "libusb-1.0")
message("LIBUSB_INCLUDE_DIR: " ${LIBUSB_INCLUDE_DIR})
find_library(LIBUSB_LIBRARY
        NAMES usb-1.0
        PATH_SUFFIXES "lib" "lib32" "lib64")
message("LIBUSB_LIBRARY: " ${LIBUSB_LIBRARY})
target_include_directories(lsusb PUBLIC ${LIBUSB_INCLUDE_DIR} ${CURL_INCLUDE_PATH})
target_link_libraries(lsusb ${LIBUSB_LIBRARY} ${CURL_LIBRARIES})
## add lsusb end

add_executable(cpopen cpopen.c)
add_executable(pointer_test pointer_test.c)
add_executable(cdata cdata.c)

project(hello_cpp CXX)
add_executable(hello_class
        cpp/hello_class.cpp)
add_executable(vector_for_each
        cpp/vector_for_each.cpp)

add_subdirectory(linux)

add_subdirectory(android/ndk)