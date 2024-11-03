cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
        main.cpp
        hw_if/pico_hardware_interface.cpp
        wifi/WiFiConnector.cpp
        wifi/hotspot_request_router.cpp
        wifi/dhcpserver/dhcpserver.c
        wifi/dnsserver/dnsserver.c
        wifi/flash/flash_hardware_imp.c
        wifi/flash/flash_writer.cpp
        wifi/flash/flash_parameters_reader.cpp
        wifi/flash/flash_hardware.cpp
        wifi/hw_if/wifi_hardware_interface.cpp
        wifi/input_form/html_renderer.cpp
        wifi/input_form/input_form_renderer.cpp
        wifi/input_form/ssid_password_input_form_renderer.cpp
        wifi/input_form/ssid_password_submitter.cpp
        wifi/input_form/percent_decoder.cpp
        wifi/tcpserver/pico_tcp_server.c
        wifi/tcpserver/pico_tcp_server.cpp
        wifi/tcpserver/http_response_packager.cpp
)
target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/hotspot # for our common lwipopts
        hw_if
        rest
        )
pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)
target_link_libraries(
        test
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        hardware_flash)