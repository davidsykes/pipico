#include "null_configuration.h"

NullConfiguration::NullConfiguration()
{
    hotspot_name = "pico2";
    hotspot_password = "password";
}


std::string NullConfiguration::process_request(const char *request, const char *params)
{
    return "Hello null";
}
