#include "logic/common.h"
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"

int main()
{
   const char* input_form_hotspot_name = "Pico Test Unit";

   initialise_pico_stdio();

   WiFiConnector connector;
   connector.ConnectToWiFi(input_form_hotspot_name);

   DEBUG_printf("Connected");
}