#pragma once
#include "itcp_response_analyser.h"
#include "irest_handler.h"

class TcpResponseAnalyser : public ITcpResponseAnalyser
{
	virtual bool AnalyseTcpResponse(const std::string& request, const std::string& response);
};
