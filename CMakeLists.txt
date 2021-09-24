cmake_minimum_required(VERSION 3.13)

project(untitled2)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/opt/curl/include)

add_executable(untitled2
        main.cpp
        module/sys/sys.cpp
        module/sys/sys.h
        module/sftp/sftp.cpp
        module/sftp/sftp.h
        module/sftp/ftp.cpp
        module/sftp/ftp.h
        module/auth/auth.cpp
        module/auth/auth.h)

target_link_libraries(untitled2 /usr/local/opt/curl/lib/libcurl.dylib)

add_executable(sftp_test sftp_test/sftp_test.cpp)

target_link_libraries(sftp_test /usr/local/opt/curl/lib/libcurl.dylib)

#export LDFLAGS="-L/usr/local/opt/curl/lib"
#export CPPFLAGS="-I/usr/local/opt/curl/include"