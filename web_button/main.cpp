#include "hw_if/pico_hardware_interface.h"
#include "wifi/WiFiConnector.h"
#include "../rest/rest_library.h"

#define JB_IP   "192.168.1.126"
#define JB_PORT 5002
#define URL     "/PlayCollection/7"

int main()
{

    IHardwareInterface* _hw_if = new PicoHardwareInterface();
    IHardwareInterface& hw_if = *_hw_if;
    hw_if.initialise_pico_stdio(true);
    hw_if.set_led(false);
    printf("Start..\n");

    WiFiConnector* wifi = new WiFiConnector();
    wifi->ConnectToWiFi(hw_if, "Button", "12345678");
    printf("Connected to wifi\n");


    // TcpResponseAnalyser tcpResponseAnalyser;
    // TcpRequestErrorLogger tcpRequestErrorLogger;
    // TcpRequestMaker tcpRequestMaker(
    //     JB_IP,
    //     JB_PORT,
    //     hw_if,
    //     tcpResponseAnalyser,
    //     tcpRequestErrorLogger);
    // RestHandler _restHandler(tcpRequestMaker);
    // IRestHandler& restHandler(_restHandler);
    RestLibrary restLibrary(JB_IP, JB_PORT);
    IRestHandler& restHandler(restLibrary);

    hw_if.initialise_input_pin(2);

    while(1)
    {
        while (hw_if.gpio_get(2)){}
        hw_if.set_led(true);
        printf("\nWaiting..\n");

        while (!hw_if.gpio_get(2)) {}
        hw_if.set_led(false);

        std::string response = restHandler.Get(URL);
        if (response.find("OK\r\n"))
        {
            printf("Result = %s\n", response.c_str());
            hw_if.set_led(true);
        }
        else
        {
            printf("Result = %s\n", response.c_str());
        }
    }

    printf("Ended..\n");
}