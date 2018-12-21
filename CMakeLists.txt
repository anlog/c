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