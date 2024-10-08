#include "hw_if/pico_hardware_interface.h"
#include "gpio/gpio.h"
#include "wifi/WiFiConnector.h"
#include "tools/message_logger.h"
#include "codes/ir_codes_repository.h"
#include "codes/code_sequence_repository.h"
#include "tcp_server/http_response_packager.h"
#include "tcp_server/pico_tcp_server.h"
#include "api/api_actions/home_display_action.h"
#include "api/api_actions/raw_display_action.h"
#include "api/api_actions/log_display_action.h"
#include "api/api_actions/codes_display_action.h"
#include "api/api_actions/code_sequences_display_action.h"
#include "api/api_actions/play_ir_code_action.h"
#include "api/api_actions/play_ir_sequence_action.h"
#include "api/formatters/code_display_formatter.h"
#include "pico_scope/pico_scope_main.h"
#include "transmit/ir_code_sender.h"
#include "main.cxx"

#define TRANSMIT_PIN 14

int main()
{
   PicoHardwareInterface phw_if;
   IHardwareInterface& hw_if = phw_if;
   hw_if.initialise_pico_stdio(false);

   WiFiConnector connector;
   connector.ConnectToWiFiDirect(hw_if, WIFI_SSID, WIFI_PASSWORD);

   GPIOInputPin actionPin(2, hw_if);
   actionPin.SetPullUp(0);
   int actionValue = actionPin.Value();
   printf("Action %d\n", actionValue);

   if (actionValue == 1)
   {
      Blinker blinker(hw_if);
      pico_scope_main(hw_if, blinker);
   }
   else
   {
      GPIOOutputPin _outputPin(TRANSMIT_PIN, hw_if);
      IGPIOOutputPin& outputPin = _outputPin;
      MessageLogger messageLogger;
      LogDisplayAction logDisplayAction(messageLogger);

      IrCodesRepository irCodesRepository(messageLogger);
      CodeDisplayFormatter codeDisplayFormatter;
      CodesDisplayAction codesDisplayAction(irCodesRepository, codeDisplayFormatter);

      CodeSequenceRepository codeSequenceRepository(messageLogger);
      ButtonFormatter buttonFormatter;
      CodeSequencesDisplayAction codeSequencesDisplayAction(codeSequenceRepository, buttonFormatter);

      HomeDisplayAction homeDisplayAction(codeSequencesDisplayAction, logDisplayAction);
      RawDisplayAction rawDisplayAction(codesDisplayAction, logDisplayAction);

      IrCodeSender irCodeSender(outputPin);
      PlayIrCodeAction playIrCodeAction(irCodeSender, irCodesRepository, homeDisplayAction);

      IrSequenceSender irSequenceSender(irCodesRepository, irCodeSender);
      PlayIrSequenceAction playIrSequenceAction(irSequenceSender, codeSequenceRepository, homeDisplayAction);

      HttpRequestRouter httpRequestRouter(homeDisplayAction, rawDisplayAction, playIrCodeAction, playIrSequenceAction);
      HttpResponsePackager httpResponsePackager(httpRequestRouter);
      hw_if.set_led(true);
      main_pico_tcp_server(&httpResponsePackager);
   }

   hw_if.cyw43_arch_deinit();
   printf("Ended..\n");
}
