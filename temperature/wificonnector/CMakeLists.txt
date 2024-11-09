# It is not recommended to build dynamic libraries.
add_library(wificonnector INTERFACE)

target_sources(wificonnector INTERFACE
src/wificonnector.cpp
src/dhcpserver/dhcpserver.c
src/dnsserver/dnsserver.c
src/hotspot_request_router.cpp
src/flash/flash_hardware_imp.c
src/flash/flash_hardware.cpp
src/flash/flash_parameters_reader.cpp
src/flash/flash_writer.cpp
src/input_form/html_renderer.cpp
src/input_form/input_form_renderer.cpp
src/input_form/percent_decoder.cpp
src/input_form/ssid_password_input_form_renderer.cpp
src/input_form/ssid_password_submitter.cpp
src/tcpserver/http_response_packager.cpp
src/tcpserver/pico_tcp_server.c
src/tcpserver/pico_tcp_server.cpp
src/hw_if/wifi_hardware_interface.cpp
)

# For interface libraries this is not completely required. (This would likely be required for static and dynamic libraries.)
# Use caution when building static libraries as there could be internal dependencies which need to be mitigated.
target_link_libraries(wificonnector INTERFACE
    pico_multicore
    hardware_dma
    hardware_pio
    hardware_timer
)