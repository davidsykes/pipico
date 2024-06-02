#include "logic/common.h"
#include "hotspot/pico_logic.h"
#include "configurations/hotspot_configuration.h"
#include "interface/interface.h"
#include "interface/system_interface.h"
#include "logic/connecting/wifi_connector.h"
#include "logic/credentials/credentials_handler.h"
#include "logic/credentials/percent_decoder.h"
#include "logic/flash/flash_manager.h"
#include "logic/input_form/html_renderer.h"
#include "logic/input_form/input_form_renderer.h"


int main()
{
   const char* input_form_hotspot_name = "Pico Test Unit";

   SYSTEM_INTERFACE_T systemInterface;
   SetUpSystemInterface(&systemInterface);
   initialise_pico_stdio();

//   flash_test();

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
   FlashManager flashManager(&systemInterface);
   CredentialsHandler credentialsHandler(&percentDecoder, &flashManager);

   //Configuration *config = new NullConfiguration();
   //Configuration *config = new LedConfiguration();
   Configuration *config = new HotSpotConfiguration(
      input_form_hotspot_name,
      wifiConnector.lastErrorMessage.c_str(),
      &htmlRenderer,
      &inputFormRenderer,
      &credentialsHandler);

   set_up_hotspot(config);
}