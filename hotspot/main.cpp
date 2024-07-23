#include <stdio.h>
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "hw_if/hardware_interface.hpp"
#include "gpio/gpio.h"
#include "work/work.h"
#include "pico_scope/pico_scope_main.h"


#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"

int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio();

   hw_if.initialise_wifi(WIFI_SSID, WIFI_PASSWORD);

   int config =
      hw_if.gpio_get(5) * 8 +
      hw_if.gpio_get(4) * 4 +
      hw_if.gpio_get(3) * 2 +
      hw_if.gpio_get(15);
   printf("Config %d\n", config);
   if (config == 8)
   {
      run_scope(hw_if);
   }
   else if (config == 4)
   {
      printf("Pulling...\n");
      hw_if.initialise_input_pin(6);
      hw_if.gpio_set_pull_up(6, 1);
   }
   else
   {
      GPIOInputPin config0(2, hw_if);
      printf("Config pin %d\n", config0.Value());

      const char* input_form_hotspot_name = "Pico Test Unit";

      printf("About to do work\n");
      do_work(hw_if);

      WiFiConnector connector;
      connector.ConnectToWiFi(input_form_hotspot_name);
   }

   printf("Ended..");
}