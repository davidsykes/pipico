#include <stdio.h>
#include "work.h"
#include "worker.h"
#include "picow_tcp_client.h"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"
#define TEST_TCP_SERVER_IP "192.168.1.87"
#define TCP_PORT 5001

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
    Worker worker;
    REQUEST_PROCESSOR_T processor;
    processor.data_object = &worker;
    processor.get_message = &get_message;
    processor.process_data = &process_data;

    tcp_client_initialise(WIFI_SSID, WIFI_PASSWORD);

    tcp_client_run(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n");

    tcp_client_run(&processor, TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n");

    tcp_client_uninit();
    return 0;
}