cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(mylib VERSION 1.0.1 DESCRIPTION "Wifi connection tool"
        LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
include(GNUInstallDirs)
add_library(mylib SHARED
        src/wificonnector.cpp
)
set_target_properties(mylib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER api/mylib.h)
configure_file(mylib.pc.in mylib.pc @ONLY)
target_include_directories(mylib PRIVATE
        .
        src
        )
install(TARGETS mylib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/mylib.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

    target_link_libraries(
        mylib
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        hardware_flash)