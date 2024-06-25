#include <stdio.h>
#include "work.h"
#include "worker.h"
#include "picow_tcp_client.h"
#include "gpiotest.h"
#include "hardware_interface.hpp"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"
#define TEST_TCP_SERVER_IP "192.168.1.87"
#define TCP_PORT 5001
#define BUFFER_LENGTH   2048

const char* get_message(void *data_object)
{
    Worker* worker = (Worker*) data_object;
    return "";
}

void process_data(void *data_object, const char *data)
{
    printf("Received Packet\n%s\n", data);
    Worker* worker = (Worker*) data_object;
    printf("Worker %d\n", worker->number());
}

int do_work()
{
    PicoHardwareInterface ph = PicoHardwareInterface();
    IHardwareInterface& hwif = ph;

    int count = 6;
    while (count-- > 0)
    {
        hwif.set_led(1);
        hwif.sleep_us(100000);
        hwif.set_led(0);
        hwif.sleep_us(100000);
    }

    // sSystem* hw_if = create_hardware_interface();
    // main_gpio(hw_if);

    Worker worker;
    REQUEST_PROCESSOR_T processor;
    processor.data_object = &worker;
    processor.get_message = &get_message;
    processor.process_data = &process_data;

    char buffer[BUFFER_LENGTH];

    tcp_client_initialise(WIFI_SSID, WIFI_PASSWORD);

    run_tcp_client_test(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, BUFFER_LENGTH);
    printf("--Restule 1--\n%s\n+++", buffer);

    run_tcp_client_test(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, BUFFER_LENGTH);
    printf("--Restule 2--\n%s\n+++", buffer);

    tcp_client_uninit();
    return 0;
}