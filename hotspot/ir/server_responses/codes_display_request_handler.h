#pragma once

class ICodesDisplayRequestHandler
{
public:
	virtual std::string HandleRequest(const std::string& request) = 0;
};

class CodesDisplayRequestHandler : public ICodesDisplayRequestHandler
{
	virtual std::string HandleRequest(const std::string& request);
};