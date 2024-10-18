#pragma once
#include "../../wifi/input_form/irenderer.h"

class MockRenderer : public IRenderer
{
	std::string requestType;

	virtual std::string Render() { return requestType; };
	virtual std::string Render(const std::string& p) { return requestType + " " + p; };

public:
	MockRenderer(const char* type) : requestType(type) {}
};
