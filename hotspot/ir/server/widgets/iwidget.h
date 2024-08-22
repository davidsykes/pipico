#pragma once
#include <string>

class IWidget
{
public:
	virtual std::string RenderWidget() = 0;
};