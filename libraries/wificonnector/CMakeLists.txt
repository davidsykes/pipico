cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(wificonnector C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_library(wificonnector
        src/wificonnector.cpp
)
