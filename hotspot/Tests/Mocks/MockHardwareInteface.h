#pragma once
#include "hardware_interface.h"

class IMockHardwareInterface : public IHardwareInterface
{
	virtual sHardwareInterface* raw_if() { return 0; }
	virtual void initialise_pico_stdio() {}
	virtual int initialise_wifi(const char* ssid, const char* password) { return 0; }
	virtual uint64_t get_time_us() { return 0; }
	virtual void initialise_input_pin(int pin_number) {}
	virtual void initialise_output_pin(int pin_number) {}
	virtual int gpio_get(int pin_number) { return 0; }
	virtual uint64_t wait_value(int pin_number, int value, uint64_t timeout) { return 0; }
	virtual void gpio_put(int pin_number, int value) {}
	virtual void set_led(bool value) {}
	virtual void sleep_us(int useconds) {}
	virtual std::string tcp_request(const char* server, unsigned int port, const char* request) { return ""; };
	virtual void tcp_client_uninit() {};
public:
};

