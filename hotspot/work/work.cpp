#include <stdio.h>
#include "work.h"
#include "worker.h"
#include "picow_tcp_client.h"
#include "hardware_interface.hpp"
#include "pico_scope/pico_scope.h"

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

int do_work(IHardwareInterface& hwif)
{
    hwif.set_led(1);
    
    int config =
        hwif.gpio_get(5) * 8 +
        hwif.gpio_get(4) * 4 +
        hwif.gpio_get(3) * 2 +
        hwif.gpio_get(15);
    printf("Config %d\n", config);
    
    int value = hwif.gpio_get(15);
    printf("Start value %d\n");
    uint64_t t = hwif.wait_value(15, 1-value, 10000000);
    printf("Change %d\n", (int)t);

    PicoScope scope = PicoScope(hwif);
    PicoScopeTrace trace = scope.FetchTrace(15);
    printf("Trace %s\n", trace.gethtml().c_str());

    Worker worker;
    REQUEST_PROCESSOR_T processor;
    processor.data_object = &worker;
    processor.get_message = &get_message;
    processor.process_data = &process_data;

    char buffer[BUFFER_LENGTH];
    tcp_client_initialise(hwif.raw_if(), WIFI_SSID, WIFI_PASSWORD);

    run_tcp_client_test(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, BUFFER_LENGTH);
    printf("--Restule 1--\n%s\n+++", buffer);

    run_tcp_client_test(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, BUFFER_LENGTH);
    printf("--Restule 2--\n%s\n+++", buffer);

    tcp_client_uninit();
    return 0;
}