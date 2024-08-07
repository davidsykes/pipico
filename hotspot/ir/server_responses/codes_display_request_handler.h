#pragma once

class ICodesDisplayRequestHandler
{
public:
	virtual std::string HandleRequest(const std::string& request) = 0;
};