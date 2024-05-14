#include <stdio.h>
#include "interface.h"
#include "configurations/null_configuration.h"

int main()
{

   Configuration *config = new NullConfiguration();

   set_up_hotspot(config);
}