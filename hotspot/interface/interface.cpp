#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "hotspot/picow_access_point.h"

#define SIZE_ERROR "<html><body><h1>FORM CONTENT EXCEEDS BUFFER</h1></body></html>"

int process_request(void *configuration, const char *request, const char *params, char *result, size_t max_result_len)
 {
    Configuration* config = (Configuration*)configuration;
    std::string process_result = config->process_request(request, params);
    int result_length = process_result.length();
    if (result_length < max_result_len - 1)
    {
      strcpy(result, process_result.c_str());
      return result_length;
    }
    printf("Request size %d exceeded limit of %d\n", result_length, max_result_len);
    strcpy(result, SIZE_ERROR);
    return strlen(SIZE_ERROR);
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
