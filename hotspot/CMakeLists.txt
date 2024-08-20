cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
        main.cpp
        hotspot/WiFiConnector.cpp
        hotspot/low_level/tcp/dhcpserver/dhcpserver.c
        hotspot/low_level/tcp/dnsserver/dnsserver.c
        hotspot/low_level/tcp/tcp_server_implementation.c
        hotspot/low_level/tcp/tcp_server.cpp
        hotspot/low_level/flash_program.c
        hotspot/logic/flash/flash_hardware.cpp
        hotspot/logic/flash/flash_manager.cpp
        hotspot/logic/input_form/html_renderer.cpp
        hotspot/logic/input_form/input_form_renderer.cpp
        hotspot/logic/credentials/credentials_handler.cpp
        hotspot/logic/credentials/percent_decoder.cpp
        hotspot/logic/connecting/wifi_connection_maker.cpp
        hotspot/logic/requests/hotspot_configuration.cpp
        hw_if/hardware_interface.c
        hw_if/pico_hardware_interface.cpp
        hw_if/picow_tcp_client.c
        gpio/gpio_input.cpp
        pico_scope/pico_scope_main.cpp
        pico_scope/pico_scope.cpp
        pico_scope/pico_scope_trace.cpp
        pico_scope/trace_data_formatter.cpp
        rest/rest_handler.cpp
        rest/tcp_response_analyser.cpp
        ir/ir_main.cpp
        ir/codes/ir_code_repository.cpp
        ir/server/http_request_router.cpp
        ir/server/http_server_home_handler.cpp
        ir/server/http_response_packager.cpp
        ir/server_responses/codes_display_request_handler.cpp
        ir/server_responses/codes_record_request_handler.cpp
        3rd_party/pico_tcp_server.c
        3rd_party/pico_tcp_server.cpp
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