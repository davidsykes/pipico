#include "tcp_request_maker.h"


int TcpRequestMaker::MakeRequest(const std::string& request, std::string& response)
{
	std::string server_response;
	hw_if.tcp_request(server.c_str(), port, request.c_str(), server_response);

	int status_code = tcpResponseAnalyser.AnalyseTcpResponse(server_response, response);

	return status_code;
}