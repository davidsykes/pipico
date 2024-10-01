cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
        main.cpp
        api/http_request_router.cpp
        api/api_actions/log_display_action.cpp
        api/api_actions/home_display_action.cpp
        api/api_actions/raw_display_action.cpp
        api/api_actions/codes_display_action.cpp
        api/api_actions/code_sequences_display_action.cpp
        api/api_actions/play_ir_code_action.cpp
        api/api_actions/play_ir_sequence_action.cpp
        api/formatters/code_display_formatter.cpp
        api/formatters/button_formatter.cpp
        codes/ir_codes_repository.cpp
        codes/code_sequence_repository.cpp
        hw_if/hardware_interface.c
        hw_if/pico_hardware_interface.cpp
        hw_if/picow_tcp_client.c
        gpio/gpio_input.cpp
        gpio/gpio_output.cpp
        pico_scope/pico_scope.cpp
        pico_scope/trace_data_formatter.cpp
        pico_scope/pico_scope_trace.cpp
        pico_scope/pico_scope_capture_and_post.cpp
        pico_scope/pico_scope_main.cpp
        rest/rest_handler.cpp
        rest/tcp_request_maker.cpp
        rest/tcp_response_analyser.cpp
        tcp_server/pico_tcp_server.c
        tcp_server/pico_tcp_server.cpp
        tcp_server/http_response_packager.cpp
        tools/message_logger.cpp
        transmit/ir_code_sender.cpp
        transmit/ir_sequence_sender.cpp
        wifi/WiFiConnector.cpp
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