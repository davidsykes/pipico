#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "hotspot/picow_access_point.h"
#include "hotspot/logic.h"
#include "hotspot/flash_program.h"

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

int connect_to_wifi(Configuration *configuration)
{
   initialise_pico_stdio();
//   try_out_flash();

   CREDENTIALS_T credentials;
   if (read_flash_contents(&credentials))
   {
      printf("Found Credentials\n");
      printf("Name %s\n", credentials.hotspot_name);
      printf("Pswd %s\n", credentials.hotspot_password);
      return 0;
   }
   else
   {
      printf("Credentials not found\n");
      return set_up_hotspot(configuration);
   }
}
