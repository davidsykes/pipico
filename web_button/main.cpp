#include "hw_if/pico_hardware_interface.h"

int main()
{

    IHardwareInterface* hw_if = new PicoHardwareInterface();
    hw_if->initialise_pico_stdio(true);
    hw_if->set_led(true);

    printf("Ended..\n");
}