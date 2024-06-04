#include "logic/common.h"
#include "hotspot/c_interface.h"
#include "logic/requests/hotspot_configuration.h"
#include "logic/connecting/wifi_connector.h"
#include "logic/credentials/credentials_handler.h"
#include "logic/credentials/percent_decoder.h"
#include "logic/flash/flash_manager.h"
#include "logic/input_form/html_renderer.h"
#include "logic/input_form/input_form_renderer.h"
#include "logic/requests/process_request.h"


int main()
{
   const char* input_form_hotspot_name = "Pico Test Unit";

   initialise_pico_stdio();

//   flash_test();

   FlashHardware flashHardware;
   WiFiConnector wifiConnector(&flashHardware);
   if (wifiConnector.CredentialsAreValid() && false)
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
   FlashManager flashManager(&flashHardware);
   CredentialsHandler credentialsHandler(&percentDecoder, &flashManager);

   //Configuration *config = new NullConfiguration();
   //Configuration *config = new LedConfiguration();
   Configuration *config = new HotSpotConfiguration(
      input_form_hotspot_name,
      wifiConnector.lastErrorMessage.c_str(),
      &htmlRenderer,
      &inputFormRenderer,
      &credentialsHandler);

   REQUEST_PROCESSOR_T processor;
   processor.configuration = config;
   processor.process_request = &process_request;

   main_hotspot(
      config->hotspot_name.c_str(),
      config->hotspot_password.c_str(),
      &processor);
}