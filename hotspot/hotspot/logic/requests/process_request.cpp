#include <string.h>
#include "configuration.h"

#define SIZE_ERROR "<html><body><h1>FORM CONTENT EXCEEDS BUFFER</h1></body></html>"

#ifdef _CONSOLE
#else
void strcpy_s(char *dest, size_t max, const char*source)
{
   strcpy(dest, source);
}
#endif

size_t process_request(void *configuration, const char *request, const char *params, char *result, size_t max_result_len)
{
   Configuration* config = (Configuration*)configuration;
   std::string process_result = config->process_request(request, params);
   size_t result_length = process_result.length();
   if (result_length < max_result_len - 1)
   {
      strcpy_s(result, max_result_len, process_result.c_str());
      return result_length;
   }
   strcpy_s(result, max_result_len, SIZE_ERROR);
   return strlen(SIZE_ERROR);
}

