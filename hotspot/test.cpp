#include <stdio.h>
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "hw_if/hardware_interface.hpp"
#include "work/gpio/gpio.h"
#include "work/work.h"

int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio();

   GPIOInputPin config0(2, hw_if);
   printf("Config pin %d\n", config0.Value());

   const char* input_form_hotspot_name = "Pico Test Unit";

   printf("About to do work\n");
   do_work(hw_if);

   WiFiConnector connector;
   connector.ConnectToWiFi(input_form_hotspot_name);

   printf("Ended..");
}