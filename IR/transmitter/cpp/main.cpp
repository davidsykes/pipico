#include "hw_if/pico_hardware_interface.h"
#include "gpio/gpio.h"
#include "wifi/WiFiConnector.h"
#include "tools/message_logger.h"
#include "codes/ir_codes_repository.h"
#include "tcp_server/http_response_packager.h"
#include "tcp_server/pico_tcp_server.h"
#include "api/api_actions/home_display_action.h"
#include "api/api_actions/log_display_action.h"
#include "api/api_actions/record_ir_action.h"
#include "api/api_actions/codes_display_action.h"
#include "api/api_actions/play_ir_action.h"
#include "api/formatters/code_display_formatter.h"
#include "pico_scope/pico_scope_configuration.h"
#include "pico_scope/pico_scope_record_and_post.h"
#include "transmit/ir_signal_sender.h"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"
#define TRANSMIT_PIN 14

int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio();

   WiFiConnector connector;
   connector.ConnectToWiFiDirect(hw_if, WIFI_SSID, WIFI_PASSWORD);

   GPIOInputPin actionPin(2, hw_if);
   actionPin.SetPullUp(0);
   int actionValue = actionPin.Value();
   printf("Action %d\n", actionValue);

   if (actionValue == 1)
   {
      RunScope(hw_if);
   }
   else
   {
      GPIOOutputPin _outputPin(TRANSMIT_PIN, hw_if);
      IGPIOOutputPin& outputPin = _outputPin;
      // int value = 0;
      // uint64_t now = outputPin.SetValueAt(value, 0);
      // while (actionValue == actionPin.Value())
      // {
      //    value = 1 - value;
      //    now += 1000000;
      //    outputPin.SetValueAt(value, now);
      // }

      MessageLogger messageLogger;
      IrCodesRepository irCodesRepository;

      LogDisplayAction logDisplayAction(messageLogger);
      CodeDisplayFormatter codeDisplayFormatter;
      CodesDisplayAction codesDisplayAction(irCodesRepository, codeDisplayFormatter);
      HomeDisplayAction homeDisplayAction(codesDisplayAction, logDisplayAction);

      PicoScopeConfiguration ir_scope_configuration(6);
      PicoScopeRecorder picoScopeRecorder(hw_if, ir_scope_configuration);
      RecordIrAction recordIrAction(picoScopeRecorder);

      IrSignalSender irSignalSender(outputPin);
      PlayIrAction playIrAction(irSignalSender, irCodesRepository);

      ((ApiAction&)playIrAction).Action("testcode");

      HttpRequestRouter httpRequestRouter(homeDisplayAction, recordIrAction, playIrAction);
      HttpResponsePackager httpResponsePackager(httpRequestRouter);
      main_pico_tcp_server(&httpResponsePackager);
   }

   hw_if.cyw43_arch_deinit();
   printf("Ended..");
}
