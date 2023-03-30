// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
extern "C"
{
#include "..\..\src\system.h"
#include "..\..\src\modulate.h"
}
#include "test_modulator.hpp"
#include "test_gpio_pin.hpp"

void mock_initialise_input_pin(int pin_number);
void mock_initialise_output_pin(int pin_number);
int mock_gpio_get(int pin_number);
void mock_gpio_put(int pin_number, int value);
void mock_sleep_us(int useconds);

int main()
{
    std::cout << "Hello World!\n";

    run_modulator_tests();
    run_gpio_pin_tests();

    sSystem system{};

    system.initialise_input_pin = &mock_initialise_input_pin;
    system.initialise_output_pin = &mock_initialise_output_pin;
    system.gpio_get = &mock_gpio_get;
    system.gpio_put = &mock_gpio_put;
    system.sleep_us = &mock_sleep_us;

    modulate(&system);
}

void mock_initialise_input_pin(int pin_number)
{

}

void mock_initialise_output_pin(int pin_number)
{

}

int mock_gpio_get(int pin_number)
{
    return 0;
}

void mock_gpio_put(int pin_number, int value)
{

}

void mock_sleep_us(int useconds)
{

}