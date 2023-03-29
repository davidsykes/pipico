extern "C"
{
#include "pins.h"
#include "pulser.h"
#include "modulator.h"
}

sInputPin* create_mock_input_pin();
sPulser* create_mock_pulser();
void mock_pulser_pulse(sPulser* self);

void when_the_input_is_on_the_modulator_calls_the_pulse_function();
void when_the_input_is_off_the_modulator_does_not_call_the_pulse_function();

void run_modulator_tests()
{
	when_the_input_is_on_the_modulator_calls_the_pulse_function();
	when_the_input_is_off_the_modulator_does_not_call_the_pulse_function();
}


void when_the_input_is_on_the_modulator_calls_the_pulse_function()
{
	sInputPin* input_pin = create_mock_input_pin();
	sPulser* pulser = create_mock_pulser();
	sModulator* modulator = create_modulator(input_pin, pulser);

	modulator->modulate(modulator);

	if (pulser->pulse_count != 1)
	{
		*((int*)0) = 1;
	}
}

void when_the_input_is_off_the_modulator_does_not_call_the_pulse_function()
{
	sInputPin* input_pin = create_mock_input_pin();
	sPulser* pulser = create_mock_pulser();
	sModulator* modulator = create_modulator(input_pin, pulser);

	modulator->modulate(modulator);

	if (pulser->pulse_count != 0)
	{
		*((int*)0) = 1;
	}
}



sInputPin* create_mock_input_pin()
{
	sInputPin* pin = new sInputPin();
	return pin;
}

sPulser* create_mock_pulser()
{
	sPulser* pulser = new sPulser();
	pulser->pulse = &mock_pulser_pulse;
	return pulser;
}

void mock_pulser_pulse(sPulser* self)
{
	self->pulse_count = self->pulse_count + 1;
}