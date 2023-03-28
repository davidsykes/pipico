// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\..\src\system.h"
#include "..\..\src\modulate.h"

void InitialiseInputPin(int pin_number);
void InitialiseOutputPin(int pin_number);
int gpio_get(int pin_number);
void gpio_put(int pin_number, int value);
void sleep_us(int useconds);

int main()
{
    std::cout << "Hello World!\n";

    sSystem system;

    system.initialise_input_pin = &InitialiseInputPin;
    system.initialise_output_pin = &InitialiseOutputPin;
    system.gpio_get = &gpio_get;
    system.gpio_put = &gpio_put;
    system.sleep_us = &sleep_us;

    modulate(&system);
}

void InitialiseInputPin(int pin_number)
{

}

void InitialiseOutputPin(int pin_number)
{

}

int gpio_get(int pin_number)
{
    return 0;
}

void gpio_put(int pin_number, int value)
{

}

void sleep_us(int useconds)
{

}