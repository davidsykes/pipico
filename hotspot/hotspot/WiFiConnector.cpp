#include "debugprintf.h"
#include "hotspot/low_level/tcp/c_interface.h"
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

   TcpServer *config = new HotSpotConfiguration(
      input_form_hotspot_name,
      wifiConnectionMaker.lastErrorMessage.c_str(),
      &htmlRenderer,
      &inputFormRenderer,
      &credentialsHandler);

   TCP_REQUEST_PROCESSOR_T processor;
   processor.configuration = config;
   processor.process_request = &process_request;

   main_hotspot(
      config->hotspot_name.c_str(),
      config->hotspot_password.c_str(),
      &processor);
}


void WiFiConnector::ConnectToWiFiDirect(IHardwareInterface& hw_if, const char* ssid, const char* password)
{
   hw_if.initialise_wifi(ssid, password);
}

// TODO Factor this out to a server object
void WiFiConnector::ConnectToWiFiTestServer(TcpServer& tcp_server_processor)
{
   HtmlRenderer htmlRenderer;
   InputFormRenderer inputFormRenderer;

   TCP_REQUEST_PROCESSOR_T processor;
   processor.configuration = &tcp_server_processor;
   processor.process_request = &process_request;

   run_tcp_server(&processor);
}