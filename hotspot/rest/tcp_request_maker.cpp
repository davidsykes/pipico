#include "tcp_request_maker.h"



int TcpRequestMaker::MakeRequest(const std::string& request)
{
	std::string response;
	hw_if.tcp_request(server.c_str(), port, request.c_str(), response);

	return -42;
}