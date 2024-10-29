#include "WiFiConnector.h"
#include "hotspot_request_router.h"
#include "flash/flash_hardware.h"
#include "flash/flash_writer.h"
#include "flash/flash_parameters_reader.h"
#include "input_form/ssid_password_input_form_renderer.h"
#include "input_form/html_renderer.h"
#include "input_form/input_form_renderer.h"
#include "input_form/percent_decoder.h"
#include "input_form/ssid_password_input_form_renderer.h"
#include "input_form/ssid_password_submitter.h"
#include "tcpserver/http_response_packager.h"
#include "tcpserver/pico_tcp_server.h"

 void WiFiConnector::ConnectToWiFi(IHardwareInterface& hw_if, const char* input_form_hotspot_name, const char* password)
 {
    FlashHardware flashHardware;
    
    FlashParametersReader flashParametersReader_(flashHardware);
    IFlashParametersReader& flashParametersReader(flashParametersReader_);
    if (!flashParametersReader.ReadParameters())
    {
      printf("Flash parameters not found\n");
    }
    else if (!flashParametersReader.ContainsParameter("ssid"))
    {
      printf("ssid not found\n");
    }
    else if (!flashParametersReader.ContainsParameter("password"))
    {
      printf("password not found\n");
    }
    else if (hw_if.initialise_wifi_sta(
      flashParametersReader.GetParameter("ssid").c_str(),
      flashParametersReader.GetParameter("password").c_str()) != 0)
    {
      printf("Connection to wifi failed\n");
    }
    else
    {
         return;
    }

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
