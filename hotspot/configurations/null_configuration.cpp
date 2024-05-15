#include "null_configuration.h"

NullConfiguration::NullConfiguration()
{
    hotspot_name = "null_configuration";
    hotspot_password = "password";
}


std::string NullConfiguration::process_request(const char *request, const char *params)
{
    return "";
}
