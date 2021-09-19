cmake_minimum_required(VERSION 3.13)

project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2
        main.cpp
        module/sys/sys.cpp
        module/sys/sys.h
        module/sftp/sftp.cpp
        module/sftp/sftp.h)
