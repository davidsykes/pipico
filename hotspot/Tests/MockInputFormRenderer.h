#pragma once

#include "../logic/iinput_form_renderer.h"


class MockInputFormRenderer : public IInputFormRenderer
{
	virtual std::string Render();
};