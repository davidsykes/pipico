cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(rest_library_example)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(rest_library_example
    main.cpp
    ../rest/rest_library.cpp
    ../rest/rest_handler.cpp
    ../rest/tcp_request_maker.cpp
    ../rest/tcp_response_analyser.cpp
    ../rest/pico_tcp_client.cpp
    ../rest/picow_tcp_client.c
)

target_include_directories(rest_library_example PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )
pico_enable_stdio_usb(rest_library_example 1)
pico_enable_stdio_uart(rest_library_example 0)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(rest_library_example pico_stdlib pico_cyw43_arch_lwip_poll)

pico_add_extra_outputs(rest_library_example)
