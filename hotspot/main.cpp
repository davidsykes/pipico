#include <stdio.h>
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "hw_if/hardware_interface.hpp"
#include "gpio/gpio.h"
#include "pico_scope/pico_scope_main.h"


#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"

int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio();

   hw_if.initialise_wifi(WIFI_SSID, WIFI_PASSWORD);

   GPIOInputPin actionPin(2, hw_if);
   actionPin.SetPullUp(0);
   printf("Action %d\n", actionPin.Value());

   if (actionPin.Value() == 0)
   {
      run_scope(hw_if);
   }
   else
   {
      GPIOInputPin inputPin(5, hw_if);
      GPIOInputPin pullingPin(3, hw_if);
      printf("Pulling %d.\n", pullingPin.Value());
      if (pullingPin.Value())
      {
         inputPin.SetPullUp(0);
      }
      int value = -1;
      while(true)
      {
         while (value == inputPin.Value()) {}
         printf("Value %d\n", inputPin.Value());
         value = inputPin.Value();
      }
   }

   hw_if.tcp_client_uninit();
   printf("Ended..");
}