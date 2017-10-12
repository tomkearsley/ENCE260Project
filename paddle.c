#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "display.h"

int main void()
{
    system_init();
    display_init();
    
    
    while(1) {
        display_update();
        
        display_pixel_set(1,1,false);
    }
}