This is not an actual library, but a first step in creating a module that can be reused

Copy the folder into the project directory

Include the source files in the cmakelists.txt
    hw_if/pico_hardware_interface.cpp
    hw_if/hardware_interface.c
    hw_if/picow_tcp_client.c

To create an interface object

#include "hw_if/pico_hardware_interface.h"
IHardwareInterface* hw_if = new PicoHardwareInterface();