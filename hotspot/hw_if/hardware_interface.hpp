#pragma once
#include <string>
#include "hardware_interface.h"

class IHardwareInterface
{
public:
    virtual sHardwareInterface* raw_if()=0;
    virtual void initialise_pico_stdio()=0;
    virtual int initialise_wifi(const char* ssid, const char* password)=0;
    virtual uint64_t get_time_us()=0;
    virtual void initialise_input_pin(int pin_number)=0;
    virtual void initialise_output_pin(int pin_number)=0;
    virtual int gpio_get(int pin_number)=0;
    virtual uint64_t wait_value(int pin_number, int value, uint64_t timeout)=0;
    virtual void gpio_put(int pin_number, int value)=0;
    virtual void set_led(bool value)=0;
    virtual void sleep_us(int useconds)=0;
    virtual std::string tcp_request(const char* request)=0;
};


class PicoHardwareInterface : public IHardwareInterface
{
    sHardwareInterface* hardware_interface;

    virtual void initialise_pico_stdio();
    virtual int initialise_wifi(const char* ssid, const char* password);
    virtual uint64_t get_time_us();
    virtual void initialise_input_pin(int pin_number);
    virtual void initialise_output_pin(int pin_number);
    virtual int gpio_get(int pin_number);
    virtual uint64_t wait_value(int pin_number, int value, uint64_t timeout);
    virtual void gpio_put(int pin_number, int value);
    virtual void set_led(bool value);
    virtual void sleep_us(int useconds);
    virtual std::string tcp_request(const char* request);

public:
    PicoHardwareInterface();
    virtual sHardwareInterface* raw_if(){return hardware_interface;}
};
