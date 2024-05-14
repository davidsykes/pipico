#include <stdio.h>
#include "interface.h"
#include "configurations/null_configuration.h"

const char * go(int t)
{
   puts("go go go");
   return "hhg";
}

int process_request(const char *request, const char *params, char *result, size_t max_result_len)
{
   printf("Request: %s", request);
   return 0;
}

int main()
{

   Configuration config = NullConfiguration();

   set_up_hotspot(config);
}