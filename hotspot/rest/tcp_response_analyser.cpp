#include "tcp_response_analyser.h"

#define HTTP_VERSION		"HTTP/1.1"
#define HTTP_VERSION_LENGTH	8

int TcpResponseAnalyser::AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response)
{
	response = server_response;
	response_cstr = response.c_str();;
	current_line = response_cstr;
	bool processing_header = true;

	int status_code = FindStatusCode();
	FindLineEnd();
	StartNextLine();

	while (processing_header)
	{
		FindLineEnd();
		if (line_end == 0)
		{
			processing_header = false;
		}
		StartNextLine();
	}

	int data_length = FindDataLength();

	analysed_response = std::string(current_line, data_length);

	return status_code;
}

int TcpResponseAnalyser::FindStatusCode()
{
	if (strncmp(current_line, HTTP_VERSION, HTTP_VERSION_LENGTH) == 0)
	{
		current_line += HTTP_VERSION_LENGTH + 1;
		int status_code = atoi(current_line);
		return status_code;
	}
	return 400;
}

int TcpResponseAnalyser::FindDataLength()
{
	int length = atoi(current_line);
	FindLineEnd();
	StartNextLine();

	if (length <= (response.size() - (current_line - response_cstr)))
	{
		return length;
	}
	return 0;
}

void TcpResponseAnalyser::FindLineEnd()
{
	line_end = 0;
	while (!LineEndIsAtTheEndOfALine())
	{
		++line_end;
	}
}

bool TcpResponseAnalyser::LineEndIsAtTheEndOfALine()
{
	return (current_line[line_end] == 0) || current_line[line_end] == '\r' || current_line[line_end] == '\n';
}

void TcpResponseAnalyser::StartNextLine()
{
	current_line += line_end;
	if (*current_line)
	{
		if (*current_line == '\r') ++current_line;
		if (*current_line == '\n') ++current_line;
	}
}

