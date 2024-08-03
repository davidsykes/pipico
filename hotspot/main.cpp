#include <stdio.h>
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "hw_if/hardware_interface.hpp"
#include "gpio/gpio.h"
#include "pico_scope/pico_scope_main.h"
#include "ir/ir_main.h"


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
      PicoScopeConfiguration scope_config(5);
      run_scope(hw_if, scope_config);
   }
   else
   {
      run_ir_main(hw_if);
   }

   hw_if.cyw43_arch_deinit();
   printf("Ended..");
}