#include "debugprintf.h"
#include "hotspot/c_interface.h"
#include "WiFiConnector.h"
#include "logic/flash/flash_hardware.h"
#include "logic/connecting/wifi_connection_maker.h"
#include "logic/requests/hotspot_configuration.h"
#include "logic/credentials/credentials_handler.h"
#include "logic/credentials/percent_decoder.h"
#include "logic/flash/flash_manager.h"
#include "logic/input_form/html_renderer.h"
#include "logic/input_form/input_form_renderer.h"
#include "logic/requests/process_request.h"

void WiFiConnector::ConnectToWiFi(const char* input_form_hotspot_name)
{
   FlashHardware flashHardware;
   WiFiConnectionMaker wifiConnectionMaker(&flashHardware);
   if (wifiConnectionMaker.CredentialsAreValid() && false)
   {
      if (wifiConnectionMaker.ConnectToWiFi())
      {
         DEBUG_printf("wifiConnectionMaker Connected");
         return;
      }
   }

   HtmlRenderer htmlRenderer;
   InputFormRenderer inputFormRenderer;
   PercentDecoder percentDecoder;
   FlashManager flashManager(&flashHardware);
   CredentialsHandler credentialsHandler(&percentDecoder, &flashManager);

   Configuration *config = new HotSpotConfiguration(
      input_form_hotspot_name,
      wifiConnectionMaker.lastErrorMessage.c_str(),
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

// TODO Factor this out to a server object
void WiFiConnector::ConnectToWiFiTestServer()
{
   FlashHardware flashHardware;
   HtmlRenderer htmlRenderer;
   InputFormRenderer inputFormRenderer;
   PercentDecoder percentDecoder;
   FlashManager flashManager(&flashHardware);
   CredentialsHandler credentialsHandler(&percentDecoder, &flashManager);

   Configuration *config = new HotSpotConfiguration(
      "input_form_hotspot_name",
      "wifiConnectionMaker.lastErrorMessage.c_str()",
      &htmlRenderer,
      &inputFormRenderer,
      &credentialsHandler);

   REQUEST_PROCESSOR_T processor;
   processor.configuration = config;
   processor.process_request = &process_request;

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"
   main_hotspot_two(
      WIFI_SSID,
      WIFI_PASSWORD,
      &processor);
}