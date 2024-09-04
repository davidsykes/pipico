#pragma once
#include <string>

class IApiAction
{
public:
	virtual std::string ApiAction() = 0;
};