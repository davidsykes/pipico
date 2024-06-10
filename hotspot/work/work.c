#include <stdio.h>
#include "work.h"
#include "picow_tcp_client.h"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"
#define TEST_TCP_SERVER_IP "192.168.1.87"
#define TCP_PORT 5001

void process_data(void *data_object, const char *data)
{
    printf("Received Packet\n%s\n", data);
}

int do_work()
{
    REQUEST_PROCESSOR_T processor;
    processor.process_data = &process_data;



    tcp_client_initialise(WIFI_SSID, WIFI_PASSWORD);
    tcp_client_run(&processor, TEST_TCP_SERVER_IP, TCP_PORT);
}