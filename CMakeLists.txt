cmake_minimum_required(VERSION 3.7)
project(TCP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        TCP/Arley.hpp
        TCP/stdafx.cpp
        TCP/stdafx.h
        TCP/targetver.h
        TCP/TCP.cpp)

add_executable(TCP ${SOURCE_FILES})