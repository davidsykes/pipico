cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
        test.cpp
        interface/interface.cpp
        hotspot/logic.c
        hotspot/system_interface.c
        hotspot/picow_access_point.c
        hotspot/dhcpserver/dhcpserver.c
        hotspot/dnsserver/dnsserver.c
        hotspot/flash_program.c
        configurations/null_configuration.cpp
        configurations/led_configuration.cpp
        configurations/hotspot_configuration.cpp
        logic/input_form/html_renderer.cpp
        logic/input_form/input_form_renderer.cpp
        logic/credentials/credentials_handler.cpp
        logic/connecting/wifi_connector.cpp
)
target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/hotspot # for our common lwipopts
        ${CMAKE_CURRENT_LIST_DIR}/hotspot/dhcpserver
        ${CMAKE_CURRENT_LIST_DIR}/hotspot/dnsserver
        )
pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)
target_link_libraries(
        test
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        hardware_flash)