#pragma once
#include <string>

class ITcpResponseAnalyser
{
public:
	virtual int AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response) = 0;
};


class TcpResponseAnalyser : public ITcpResponseAnalyser
{
	std::string response;
	const char* response_cstr = 0;
	const char* current_line = 0;
	size_t line_end = 0;
	bool LineEndIsAtTheEndOfALine();
	void FindLineEnd();
	void StartNextLine();
	int FindStatusCode();
	int FindDataLength();

	virtual int AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response);

};
