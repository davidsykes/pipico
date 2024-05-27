#include "common.h"
#include "hotspot/logic.h"
#include "interface/interface.h"
#include "configurations/hotspot_configuration.h"
#include "hotspot/system_interface.h"
#include "logic/connecting/wifi_connector.h"
#include "../logic/input_form/html_renderer.h"
#include "../logic/input_form/input_form_renderer.h"
#include "../logic/credentials/credentials_handler.h"
#include "../logic/credentials/percent_decoder.h"

int main()
{
   const char* hotSpotName = "Pico Test Unit";

   SYSTEM_INTERFACE_T systemInterface;
   SetUpSystemInterface(&systemInterface);
   initialise_pico_stdio();
   
   WiFiConnector wifiConnector(&systemInterface);
   if (wifiConnector.CredentialsAreValid())
   {
      if (wifiConnector.ConnectToWiFi())
      {
         DEBUG_printf("Connected");
         return 0;
      }
   }

   HtmlRenderer htmlRenderer;
   InputFormRenderer inputFormRenderer;
   PercentDecoder percentDecoder;
   CredentialsHandler credentialsHandler(&percentDecoder);

   //Configuration *config = new NullConfiguration();
   //Configuration *config = new LedConfiguration();
   Configuration *config = new HotSpotConfiguration(
      hotSpotName,
      wifiConnector.lastErrorMessage.c_str(),
      &htmlRenderer,
      &inputFormRenderer,
      &credentialsHandler);

   connect_to_wifi(config);
}