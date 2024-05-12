#include <stdio.h>
#include "hotspot/picow_access_point.h"

int set_up_hotspot(
   const char* hotspot_name,
   const char* hotspot_password,
   int (*process_request)(const char *request, const char *params, char *result, size_t max_result_len),
   const char* (*go) (int))
{
   HOTSPOT_CONFIGURATION_T config;
   config.hotspot_name = hotspot_name;
   config.hotspot_password = hotspot_password;
   config.go = go;
   config.process_request = process_request;

   main_hotspot(&config);
   return 0;
}
