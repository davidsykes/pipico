#include <stdio.h>
#include "interface/interface.h"
#include "configurations/null_configuration.h"
#include "configurations/led_configuration.h"

int main()
{

   //Configuration *config = new NullConfiguration();
   Configuration *config = new LedConfiguration();

   set_up_hotspot(config);
}