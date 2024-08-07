#pragma once

class ICodesRecordRequestHandler
{
public:
	virtual std::string HandleRequest(const std::string& request) = 0;
};

