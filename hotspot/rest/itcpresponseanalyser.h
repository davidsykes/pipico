#pragma once
#include <string>


class ITcpResponseAnalyser
{
public:
	virtual void AnalyseTcpResponse(const std::string& request, const std::string& response) = 0;
};
