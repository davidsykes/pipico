#pragma once

#include "../../logic/input_form/iinput_form_renderer.h"


class MockInputFormRenderer : public IInputFormRenderer
{
	virtual std::string Render();
};