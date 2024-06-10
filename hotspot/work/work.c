#include <stdio.h>
#include "work.h"
#include "picow_tcp_client.h"

void process_data(void *data_object, const char *data)
{
    printf("Received Packet\n%s\n", data);
}

int do_work()
{
    REQUEST_PROCESSOR_T processor;
    processor.process_data = &process_data;
    tcp_client_main(&processor);
}