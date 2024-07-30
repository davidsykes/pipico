#include <stdio.h>
#include "ir_main.h"
#include "gpio/gpio.h"
//#include "rest_handler.h"
//#include "tcp_response_analyser.h"


#define IR_API_SERVER_IP "192.168.1.87"
#define IR_API_PORT 5000
#define IR_DATA_CREATE_URL "/trace"

void run_ir_main(IHardwareInterface& hw_if)
{
    printf("Run IR\n");

    GPIOInputPin actionPin(3, hw_if);
    actionPin.SetPullUp(0);
    printf("Sub action %d\n", actionPin.Value());

    if (actionPin.Value() == 0)
    {
    }

}

