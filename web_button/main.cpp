#include "hw_if/pico_hardware_interface.h"
#include "wifi/WiFiConnector.h"
#include "../rest/tcp_response_analyser.h"
#include "../rest/rest_handler.h"
#include "../rest/tcp_request_error_logger.h"
#include "../rest/tcp_request_maker.h"

#define JB_IP   "192.168.1.126"
#define JB_PORT 5002

int main()
{

    IHardwareInterface* _hw_if = new PicoHardwareInterface();
    IHardwareInterface& hw_if = *_hw_if;
    hw_if.initialise_pico_stdio(true);
    hw_if.set_led(true);
    printf("Start..\n");

    WiFiConnector* wifi = new WiFiConnector();
    wifi->ConnectToWiFi(hw_if, "Button", "12345678");
    printf("Connected to wifi\n");


    TcpResponseAnalyser tcpResponseAnalyser;
    TcpRequestErrorLogger tcpRequestErrorLogger;
    TcpRequestMaker tcpRequestMaker(
        JB_IP,
        JB_PORT,
        hw_if,
        tcpResponseAnalyser,
        tcpRequestErrorLogger);
    RestHandler _restHandler(tcpRequestMaker);
    IRestHandler& restHandler(_restHandler);

    hw_if.initialise_input_pin(2);
    while(1)
    {
        printf("\nWaiting..\n");
        int pins = hw_if.gpio_get(2);
        printf("Pins %d\n", pins);
        while (pins == hw_if.gpio_get(2)) {}
        pins = hw_if.gpio_get(2);
        printf("Pins %d\n", pins);

        std::string response = restHandler.Get("/PlayCollection/7");
        printf("Result = %s\n", response.c_str());
    }

    printf("Ended..\n");
}