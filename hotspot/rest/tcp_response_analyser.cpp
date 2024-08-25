#include "tcp_response_analyser.h"

#define CRLF_LEN 2

int TcpResponseAnalyser::AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response)
{
	analysed_response = "AnalyseTcpResponse Not Implemented Error";

	response = server_response;
	response_length = response.size();
	current_position = 0;
	bool processing_header = true;

	while (processing_header)
	{
		find_line();

		if (line_end == current_position)
		{
			processing_header = false;
		}

		next_line();
	}

	find_line();
	int data_length = atoi(response.c_str() + current_position);
	next_line();

	std::string text = response.substr(current_position, data_length);
	current_position += data_length + CRLF_LEN;

	return text == "Ok";
}

void TcpResponseAnalyser::find_line()
{
	if (current_position < response_length)
	{
		line_end = response.find("\r\n", current_position);
		if (line_end == std::string::npos)
		{
			line_end = response_length;
		}
	}
	else
	{
		line_end = response_length;
	}
}

void TcpResponseAnalyser::next_line()
{
	if (current_position < response_length)
	{
		current_position = line_end + CRLF_LEN;
	}
}