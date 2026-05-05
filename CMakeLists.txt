cmake_minimum_required(VERSION 4.2)
project(CS240Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS240Project3
        initialtest.cc
        myset.h
        setinterface.h
        myset.cc
        demo.cc)
