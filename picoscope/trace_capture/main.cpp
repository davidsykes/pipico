#include "stdio.h"
#include "hw_if/pico_hardware_interface.h"
// #include "gpio/gpio.h"
#include "pico_scope/pico_scope_main.h"
// #include "tools/message_logger.h"
#include "tools/blinker.h"
#include "wifi/WiFiConnector.h"

#define TRANSMIT_PIN 14

int main()
{
   // IHardwareInterface& hw_if = phw_if;
   // hw_if.initialise_pico_stdio(true);

   WiFiConnector connector;
   connector.ConnectToWiFi("PicoScope", "12345678");
   
   PicoHardwareInterface hw_if;

   // GPIOInputPin actionPin(2, hw_if);
   // actionPin.SetPullUp(0);
   // int actionValue = actionPin.Value();
   // printf("Action %d\n", actionValue);

   // if (actionValue == 1)
   // {
     Blinker blinker(hw_if);
     pico_scope_main(hw_if, blinker);
   // }
   // else
   // {
   // }

//   hw_if.cyw43_arch_deinit();
   printf("Ended..\n");
}
