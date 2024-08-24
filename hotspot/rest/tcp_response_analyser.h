#pragma once
#include <string>

class ITcpResponseAnalyser
{
public:
	virtual bool AnalyseTcpResponse(const std::string& request, const std::string& response) = 0;
};


class TcpResponseAnalyser : public ITcpResponseAnalyser
{
	std::string response;
	size_t current_position = 0;
	size_t response_length = 0;
	size_t line_end = 0;
	void find_line();
	void next_line();

	virtual bool AnalyseTcpResponse(const std::string& request, const std::string& response);
};
