cmake_minimum_required(VERSION 3.15)
project(advcppfinal)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(advcppfinal
        bitmap.cpp
        bitmap.h
        main.cpp)
