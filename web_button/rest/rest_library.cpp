#include "rest_library.h"

RestLibrary::RestLibrary(const char*server, int port)
{
    _pico_tcp_client = new PicoTcpClient();
    _tcp_response_analyser = new TcpResponseAnalyser();
    _tcp_request_error_logger = new TcpRequestErrorLogger();
    _tcp_request_maker = new TcpRequestMaker(
        server,
        port,
        *_pico_tcp_client,
        *_tcp_response_analyser,
        *_tcp_request_error_logger
    );
    _rest_handler = new RestHandler(*_tcp_request_maker);
};

RestLibrary::~RestLibrary()
{
    delete _rest_handler;
    delete _tcp_request_maker;
    delete _tcp_request_error_logger;
    delete _tcp_response_analyser;
    delete _pico_tcp_client;
};
std::string RestLibrary::Get(const char* url)
{
    return ((IRestHandler*)_rest_handler)->Get(url);
}

std::string RestLibrary::Put(const char* url, const char* body)
{
    return ((IRestHandler*)_rest_handler)->Put(url, body);
}
