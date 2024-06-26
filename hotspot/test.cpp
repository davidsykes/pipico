#include <stdio.h>
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "work/work.h"

int main()
{
   const char* input_form_hotspot_name = "Pico Test Unit";

   initialise_pico_stdio();

   printf("About to do work\n");
   do_work();

   WiFiConnector connector;
   connector.ConnectToWiFi(input_form_hotspot_name);

   printf("Ended..");
}