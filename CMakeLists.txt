cmake_minimum_required(VERSION 3.30)
project(imu)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE
        SRC_FILES
        Quaternion/*.cpp)

add_executable(imu main.cpp
        ${SRC_FILES})

target_include_directories(imu
        PUBLIC
        Quaternion
        Matrix
)

