#include <stdio.h>
#include "ir_main.h"
#include "gpio/gpio.h"
#include "pico_scope/pico_scope_main.h"
#include "ir_code_repository.h"
#include "../rest/itcp_response_analyser.h"
#include "../rest/tcp_response_analyser.h"
#include "../rest/rest_handler.h"


#define IR_API_SERVER_IP "192.168.1.87"
#define IR_API_PORT 5000
// #define IR_DATA_CREATE_URL "/trace"

void run_ir_main(IHardwareInterface& hw_if)
{
    printf("Run IR\n");

    GPIOInputPin actionPin(3, hw_if);
    actionPin.SetPullUp(0);
    printf("Sub action %d\n", actionPin.Value());

    if (actionPin.Value() == 0)
    {
        TcpResponseAnalyser responseAnalyser;
        RestHandler restHandler(hw_if,
                                responseAnalyser,
                                IR_API_SERVER_IP,
                                IR_API_PORT);
        IrCodeRepository codeRepository(restHandler);
        codeRepository.RetrieveCodes();
        //run_tcp_server_test();
    }
    else
    {
        PicoScopeConfiguration ir_scope_configuration(6);
        run_scope(hw_if, ir_scope_configuration);
    }

}

