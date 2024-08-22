#include "http_server_home_page.h"

std::string HttpServerHomePage::ProcessHttpRequest(const char* request)
{
    std::string display = codesDisplayRequestHandler.HandleRequest(request);
    std::string record = codesRecordRequestHandler.HandleRequest(request);
    std::string logs = logsDisplayWidget.RenderWidget();
    return display + "<br><br>" + record + "<br><br>" + logs;
}
