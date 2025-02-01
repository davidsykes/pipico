

// Code copies from pipico/libraries.hw_if



#pragma once
#include "ihardware_interface.h"
#include "hardware_interface.h"

class PicoHardwareInterface : public IHardwareInterface
{
    sHardwareInterface* hardware_interface;

    virtual void initialise_pico_stdio(bool wait_for_usb_comms);
    virtual int initialise_wifi_sta(const char* ssid, const char* password);
    virtual void initialise_wifi_ap(const char* ssid, const char* password);
    virtual uint64_t get_time_us();
    virtual void initialise_input_pin(int pin_number);
    virtual void gpio_set_pull_up(int pin_number, int value);
    virtual void initialise_output_pin(int pin_number);
    virtual int gpio_get(int pin_number);
    virtual int get_pins();
    virtual int wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout);
    virtual void gpio_put(int pin_number, bool value);
    virtual uint64_t gpio_put_at_us(int pin_number, bool value, uint64_t time_us);
    virtual void set_led(bool value);
    virtual void sleep_us(int useconds);
    virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response);
    virtual void cyw43_arch_deinit();

public:
    PicoHardwareInterface();
};
