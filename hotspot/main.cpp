#include "WiFiConnector.h"
#include "3rd_party/pico_tcp_server.h"
#include "hw_if/pico_hardware_interface.h"
#include "gpio/gpio.h"
#include "ir/codes/ir_code_repository.h"
#include "ir/server/http_request_router.h"
#include "ir/server/http_request_router.h"
#include "ir/server/pages/http_server_home_page.h"
#include "ir/server/http_server_record_handler.h"
#include "ir/server/http_response_packager.h"
#include "ir/server/widgets/log_display_widget.h"
#include "ir/ir_main.h"
#include "rest/rest_handler.h"
#include "rest/tcp_response_analyser.h"
#include "rest/tcp_request_error_logger.h"
#include "tools/message_logger.h"

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

      MessageLogger messageLogger;

      #define SCOPE_API_SERVER_IP "192.168.1.87"
      #define SCOPE_API_PORT 5000
      TcpResponseAnalyser tcp_analyser;
      TcpRequestErrorLogger tcpRequestErrorLogger;
      TcpRequestMaker tcpRequestMaker(SCOPE_API_SERVER_IP, SCOPE_API_PORT, hw_if, tcp_analyser, tcpRequestErrorLogger);
      RestHandler restHandler(tcpRequestMaker);

      IrCodeRepository irCodeRepository(restHandler);
      irCodeRepository.RetrieveCodes(messageLogger);

      CodesDisplayRequestHandler codesDisplayRequestHandler;
      CodesRecordRequestHandler codesRecordRequestHandler;
      LogDisplayWidget LogDisplayWidget(messageLogger);
      HttpServerHomePage homeHandler(codesDisplayRequestHandler, codesRecordRequestHandler, LogDisplayWidget);

      PicoScopeConfiguration ir_scope_configuration(6);
      PicoScopeRecordAndPost picoScopeRecordAndPost(hw_if, ir_scope_configuration, restHandler);
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