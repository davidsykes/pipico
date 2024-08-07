#pragma once
#include <string>

class ICodesRecordRequestHandler
{
public:
	virtual std::string HandleRequest(const std::string& request) = 0;
};

class CodesRecordRequestHandler : public ICodesRecordRequestHandler
{
	virtual std::string HandleRequest(const std::string& request);
};