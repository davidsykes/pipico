 #include <stdio.h>
#include "interface.h"

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


 int main() {

set_up_hotspot("Test Hotspot", "12345678", &process_request, &go);
 }