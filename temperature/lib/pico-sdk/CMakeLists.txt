# It is not recommended to build dynamic libraries.
add_library(lib INTERFACE)

target_sources(lib INTERFACE
    lib.cpp
)

# For interface libraries this is not completely required. (This would likely be required for static and dynamic libraries.)
# Use caution when building static libraries as there could be internal dependencies which need to be mitigated.
target_link_libraries(lib INTERFACE
    pico_multicore
    hardware_dma
    hardware_pio
    hardware_timer
)