cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(web_button)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(web_button
    main.cpp
    hw_if/pico_hardware_interface.cpp
    hw_if/hardware_interface.c
    hw_if/picow_tcp_client.c
    wifi/WiFiConnector.cpp
    wifi/hotspot_request_router.cpp
    wifi/dhcpserver/dhcpserver.c
    wifi/dnsserver/dnsserver.c
    wifi/flash/flash_hardware_imp.c
    wifi/flash/flash_writer.cpp
    wifi/flash/flash_parameters_reader.cpp
    wifi/flash/flash_hardware.cpp
    wifi/input_form/html_renderer.cpp
    wifi/input_form/input_form_renderer.cpp
    wifi/input_form/ssid_password_input_form_renderer.cpp
    wifi/input_form/ssid_password_submitter.cpp
    wifi/input_form/percent_decoder.cpp
    wifi/tcpserver/pico_tcp_server.c
    wifi/tcpserver/pico_tcp_server.cpp
    wifi/tcpserver/http_response_packager.cpp
)

target_include_directories(web_button PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        hw_if
        )
pico_enable_stdio_usb(web_button 1)
pico_enable_stdio_uart(web_button 0)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(web_button pico_stdlib pico_cyw43_arch_lwip_poll)

pico_add_extra_outputs(web_button)
