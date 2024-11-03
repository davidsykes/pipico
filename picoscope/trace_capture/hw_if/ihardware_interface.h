#pragma once
#include <string>
#include "pins_changed_data.h"

class IHardwareInterface
{
public:
    virtual uint64_t get_time_us()=0;
    virtual void initialise_input_pin(int pin_number)=0;
    virtual void gpio_set_pull_up(int pin_number, int value)=0;
    virtual int get_pins()=0;
    virtual int wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout)=0;
    virtual void set_led(bool value)=0;
    virtual void sleep_us(int useconds)=0;
    virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response)=0;
};

