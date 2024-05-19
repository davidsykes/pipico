#include <stdio.h>
#include "interface/interface.h"
#include "configurations/null_configuration.h"
#include "configurations/led_configuration.h"
#include "configurations/hotspot_configuration.h"
#include "logic/html_renderer.h"

int main()
{

   //Configuration *config = new NullConfiguration();
   //Configuration *config = new LedConfiguration();
   Configuration *config = new HotSpotConfiguration("Pico Test Unit");

   connect_to_wifi(config);
}