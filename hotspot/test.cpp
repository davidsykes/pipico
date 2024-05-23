#include <stdio.h>
#include "interface/interface.h"
#include "configurations/null_configuration.h"
#include "configurations/led_configuration.h"
#include "configurations/hotspot_configuration.h"

int main()
{
   SYSTEM_INTERFACE_T systemInterface;
   SetUpSystemInterface(&systemInterface);
   
   WifiConnector wifiConnector(&systemInteface);
   if (wifiConnector.CredentialsAreValid())
   {
      if (wifiConnector.ConnectToWifi())
      {
         DEBUG_printf("Connected");
         return;
      }
   }

   //Configuration *config = new NullConfiguration();
   //Configuration *config = new LedConfiguration();
   Configuration *config = new HotSpotConfiguration("Pico Test Unit", wifiConnector.GetErrorMessage());

   connect_to_wifi(config);
}