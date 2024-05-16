#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "hotspot/picow_access_point.h"

int process_request(void *configuration, const char *request, const char *params, char *result, size_t max_result_len)
 {
    Configuration* config = (Configuration*)configuration;
    std::string process_result = config->process_request(request, params);
    if (process_result.length() < max_result_len - 1)
    {
      strcpy(result, process_result.c_str());
      return process_result.length();
    }
    return 0;
 }

int set_up_hotspot(Configuration *configuration)
{
   HOTSPOT_CONFIGURATION_T config;
   config.hotspot_name = configuration->hotspot_name.c_str();
   config.hotspot_password = configuration->hotspot_password.c_str();
   config.configuration = configuration;
   config.process_request = &process_request;

   main_hotspot(&config);
   return 0;
}
