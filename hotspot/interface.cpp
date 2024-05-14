#include <stdio.h>
#include "interface.h"
#include "hotspot/picow_access_point.h"



 const char * go(void *configuration, int t)
 {
    puts("go go go");
    return "hhg";
 }

int process_request(void *configuration, const char *request, const char *params, char *result, size_t max_result_len)
 {
    printf("Request balbal\n\n: %s\n", request);
    Configuration* config = (Configuration*)configuration;
    printf("sdfdsfds %s\n", config->hotspot_name.c_str());
    return 0;
 }

int set_up_hotspot(Configuration *configuration)
{
   HOTSPOT_CONFIGURATION_T config;
   config.hotspot_name = configuration->hotspot_name.c_str();
   config.hotspot_password = configuration->hotspot_password.c_str();
   config.configuration = configuration;
   config.go = &go;
   config.process_request = &process_request;

   main_hotspot(&config);
   return 0;
}
