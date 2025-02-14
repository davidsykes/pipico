#pragma once
#include <string>
#include "pins_changed_data.h"

class IHardwareInterface
{
public:
    virtual void initialise_pico_stdio(bool wait_for_usb_comms)=0;
    virtual int initialise_wifi_sta(const char* ssid, const char* password)=0;
    virtual void initialise_wifi_ap(const char* ssid, const char* password)=0;
    virtual uint64_t get_time_us()=0;
    virtual void initialise_input_pin(int pin_number)=0;
    virtual void gpio_set_pull_up(int pin_number, int value)=0;
    virtual void initialise_output_pin(int pin_number)=0;
    virtual int gpio_get(int pin_number)=0;
    virtual int get_pins()=0;
    virtual int wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout)=0;
    virtual void gpio_put(int pin_number, bool value)=0;
    virtual uint64_t gpio_put_at_us(int pin_number, bool value, uint64_t time_us)=0;
    virtual void set_led(bool value)=0;
    virtual void sleep_us(int useconds)=0;
    virtual void cyw43_arch_deinit()=0;
};

