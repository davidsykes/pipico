#pragma once
#include "itcpresponseanalyser.h"
#include "iresthandler.h"

class TcpResponseAnalyser : public ITcpResponseAnalyser
{
	virtual bool AnalyseTcpResponse(const std::string& request, const std::string& response);
};
