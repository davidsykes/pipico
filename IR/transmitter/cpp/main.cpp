#include "hw_if/pico_hardware_interface.h"
#include "gpio/gpio.h"
#include "wifi/WiFiConnector.h"
#include "tools/message_logger.h"
#include "codes/ir_code_repository.h"
#include "tcp_server/http_response_packager.h"
#include "tcp_server/pico_tcp_server.h"
#include "api/api_actions/log_display_action.h"
#include "pico_scope/pico_scope_configuration.h"

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
   connector.ConnectToWiFiDirect(hw_if, WIFI_SSID, WIFI_PASSWORD);

   MessageLogger messageLogger;
   IrCodeRepository irCodeRepository;

   //CodesDisplayRequestHandler codesDisplayRequestHandler;
   //CodesRecordRequestHandler codesRecordRequestHandler;
   LogDisplayAction logDisplayAction(messageLogger);
   //HttpServerHomePage homeHandler(/*codesDisplayRequestHandler, codesRecordRequestHandler,*/ LogDisplayWidget);

   //PicoScopeConfiguration ir_scope_configuration(6);
   //PicoScopeRecordAndPost picoScopeRecordAndPost(hw_if, ir_scope_configuration, restHandler);
   //HttpServerRecordHandler recordHandler(picoScopeRecordAndPost);

   HttpRequestRouter httpRequestRouter(logDisplayAction, logDisplayAction);
   HttpResponsePackager httpResponsePackager(httpRequestRouter);
   main_pico_tcp_server(&httpResponsePackager);

   hw_if.cyw43_arch_deinit();
   printf("Ended..");
}