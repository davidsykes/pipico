#pragma once
#include <string>


class ITcpResponseAnalyser
{
public:
	virtual bool AnalyseTcpResponse(const std::string& request, const std::string& response) = 0;
};
