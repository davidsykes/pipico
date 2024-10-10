// #include "debugprintf.h"
#include "WiFiConnector.h"
#include "hotspot_request_router.h"
#include "tcpserver/http_response_packager.h"
#include "tcpserver/pico_tcp_server.h"
//#include "tcp_server_implementation.h"
// #include "logic/flash/flash_hardware.h"
// #include "logic/connecting/wifi_connection_maker.h"
// #include "logic/requests/hotspot_configuration.h"
// #include "logic/credentials/credentials_handler.h"
// #include "logic/credentials/percent_decoder.h"
// #include "logic/flash/flash_manager.h"
// #include "logic/input_form/html_renderer.h"
// #include "logic/input_form/input_form_renderer.h"

 void WiFiConnector::ConnectToWiFi(IHardwareInterface& hw_if, const char* input_form_hotspot_name, const char* password, const char* tempssid, const char* temppassword)
 {
//    FlashHardware flashHardware;
//    WiFiConnectionMaker wifiConnectionMaker(&flashHardware);
//    if (wifiConnectionMaker.CredentialsAreValid() && false)
//    {
//       if (wifiConnectionMaker.ConnectToWiFi())
//       {
//          DEBUG_printf("wifiConnectionMaker Connected");
//          return;
//       }
//    }

//    HtmlRenderer htmlRenderer;
//    InputFormRenderer inputFormRenderer;
//    PercentDecoder percentDecoder;
//    FlashManager flashManager(&flashHardware);
//    CredentialsHandler credentialsHandler(&percentDecoder, &flashManager);

//    HotSpotTcpServer *config = new HotSpotConfiguration(
//       input_form_hotspot_name,
//       wifiConnectionMaker.lastErrorMessage.c_str(),
//       &htmlRenderer,
//       &inputFormRenderer,
//       &credentialsHandler);

   // TCP_REQUEST_PROCESSOR_T processor;
   // processor.configuration = 0; //config;
   // processor.process_request = &process_request;
   // printf("Going iddddn\n");

   // main_hotspot(
   //    "Pico", //config->hotspot_name.c_str(),
   //    "12345678", //config->hotspot_password.c_str(),
   //    &processor);

   ConnectToWiFiDirect(hw_if, tempssid, temppassword);
   
   HotSpotRequestRouter httpRequestRouter;
   HttpResponsePackager httpResponsePackager(httpRequestRouter);
   run_tcp_server(&httpResponsePackager);
}


void WiFiConnector::ConnectToWiFiDirect(IHardwareInterface& hw_if, const char* ssid, const char* password)
{
   hw_if.initialise_wifi_sta(ssid, password);
}

// // TODO Factor this out to a server object
// void WiFiConnector::ConnectToWiFiTestServer(HotSpotTcpServer& tcp_server_processor)
// {
//    HtmlRenderer htmlRenderer;
//    InputFormRenderer inputFormRenderer;

//    TCP_REQUEST_PROCESSOR_T processor;
//    processor.configuration = &tcp_server_processor;
//    processor.process_request = &process_request;

//    run_tcp_server(&processor);
// }