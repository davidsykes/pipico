cmake_minimum_required(VERSION 3.13)
project(mylib VERSION 1.0.1 DESCRIPTION "Wifi connection tool")
add_library(mylib SHARED
        src/wificonnector.cpp
)
set_target_properties(mylib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(mylib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(mylib PROPERTIES PUBLIC_HEADER inlude/mylib.h)
target_include_directories(mylib PRIVATE
        .
        src
        )

