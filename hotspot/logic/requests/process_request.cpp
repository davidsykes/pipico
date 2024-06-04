#include <string.h>
#include "configuration.h"

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

