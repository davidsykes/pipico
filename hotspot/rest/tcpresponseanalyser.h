#pragma once
#include "itcpresponseanalyser.h"
#include "iresthandler.h"

class TcpResponseAnalyser : public ITcpResponseAnalyser
{
	IRestHandler& restHandler;

	virtual void AnalyseTcpResponse(const std::string& request, const std::string& response);

public:
	TcpResponseAnalyser(IRestHandler& restHandler) : restHandler(restHandler) {}
};
