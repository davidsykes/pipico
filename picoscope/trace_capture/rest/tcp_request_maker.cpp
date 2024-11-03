#include "tcp_request_maker.h"
#include <sstream>

int TcpRequestMaker::MakeRequest(const std::string& request, std::string& response)
{
	std::string server_response;
	int tcp_request_result = hw_if.tcp_request(server.c_str(), port, request.c_str(), server_response);

	if (tcp_request_result == 0)
	{
		tcpRequestErrorLogger.LogError(tcp_request_result, server, port, request, server_response);
		return ExtractStatusAndBody(server_response, response);
	}
	else
	{
		tcpRequestErrorLogger.LogError(tcp_request_result, server, port, request, server_response);
		return MakeServerErrorResponse(tcp_request_result, response);
	}
}

int TcpRequestMaker::ExtractStatusAndBody(const std::string& server_response, std::string& response)
{
	int status_code = tcpResponseAnalyser.AnalyseTcpResponse(server_response, response);

	return status_code;
}

int TcpRequestMaker::MakeServerErrorResponse(int tcp_request_result, std::string& response)
{
	std::ostringstream str;
	str << "tcp error " << tcp_request_result;
	response = str.str();
	return 500;
}