#pragma once
#include "ihardware_interface.h"

class PicoHardwareInterface : public IHardwareInterface
{
    virtual uint64_t get_time_us();
    virtual void initialise_input_pin(int pin_number);
    virtual void gpio_set_pull_up(int pin_number, int value);
    virtual int get_pins();
    virtual int wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout);
    virtual void set_led(bool value);
    virtual void sleep_us(int useconds);
    virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response);
};
