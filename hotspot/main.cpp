#include "WiFiConnector.h"
#include "hw_if/pico_hardware_interface.h"
#include "gpio/gpio.h"
#include "ir/server/http_request_router.h"
#include "3rd_party/pico_tcp_server.h"
#include "ir/server/http_request_router.h"
#include "ir/server/http_server_home_handler.h"
#include "ir/server/http_server_record_handler.h"
#include "ir/server/http_response_packager.h"
#include "ir/ir_main.h"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"



int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio();

   GPIOInputPin actionPin(2, hw_if);
   actionPin.SetPullUp(0);
   printf("Action %d\n", actionPin.Value());

   WiFiConnector connector;
   if (actionPin.Value() == 0)
   {
      connector.ConnectToWiFi("Ye hot spot");
      // PicoScopeConfiguration scope_config(5);
      // run_scope(hw_if, scope_config);
   }
   else
   {
      connector.ConnectToWiFiDirect(hw_if, WIFI_SSID, WIFI_PASSWORD);

      CodesDisplayRequestHandler codesDisplayRequestHandler;
      CodesRecordRequestHandler codesRecordRequestHandler;
      HttpServerHomeHandler homeHandler(codesDisplayRequestHandler, codesRecordRequestHandler);
      PicoScopeConfiguration ir_scope_configuration(6);
      PicoScopeRecordAndPost picoScopeRecordAndPost(hw_if, ir_scope_configuration);
      HttpServerRecordHandler recordHandler(picoScopeRecordAndPost);
      HttpRequestRouter httpRequestRouter(homeHandler, recordHandler);
      HttpResponsePackager httpResponsePackager(httpRequestRouter);
      main_pico_tcp_server(&httpResponsePackager);
      run_ir_main(hw_if, connector);
   }

   // printf("BAD BAD Connected..\n");

   // hw_if.initialise_wifi(WIFI_SSID, WIFI_PASSWORD);

   hw_if.cyw43_arch_deinit();
   printf("Ended..");
}