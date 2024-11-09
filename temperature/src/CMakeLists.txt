
add_executable(test
  main.cpp
)
target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ../include
        ../lib
        )


# enable usb output, disable uart output
pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)

target_link_libraries(
        test
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        hardware_flash
        lib
)

# linker options
target_link_options(test 
    PRIVATE "LINKER:--print-memory-usage"
)