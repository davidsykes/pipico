#include "WiFiConnector.h"
#include "hotspot_request_router.h"
#include "flash/flash_hardware.h"
#include "flash/flash_writer.h"
#include "input_form/ssid_password_input_form_renderer.h"
#include "input_form/html_renderer.h"
#include "input_form/input_form_renderer.h"
#include "input_form/percent_decoder.h"
#include "input_form/ssid_password_input_form_renderer.h"
#include "input_form/ssid_password_submitter.h"
#include "tcpserver/http_response_packager.h"
#include "tcpserver/pico_tcp_server.h"

 void WiFiConnector::ConnectToWiFi(IHardwareInterface& hw_if, const char* input_form_hotspot_name, const char* password, const char* tempssid, const char* temppassword)
 {
    FlashHardware flashHardware;
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

   //ConnectToWiFiDirect(hw_if, tempssid, temppassword);
   hw_if.initialise_wifi_ap(input_form_hotspot_name, password);
   
   HtmlRenderer htmlRenderer;
   InputFormRenderer inputFormRenderer;
   SSIDPasswordInputFormRenderer ssidPasswordInputFormRenderer("PicoIR", htmlRenderer, inputFormRenderer);
   FlashWriter flashWriter(flashHardware);
   PercentDecoder percentDecoder;
   SSIDPasswordSubmitter ssidPasswordSubmitter(flashWriter, percentDecoder);
   HotSpotRequestRouter httpRequestRouter(ssidPasswordInputFormRenderer, ssidPasswordSubmitter);
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