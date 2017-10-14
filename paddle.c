#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pio.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

int paddlecheck(int paddlex){
    
        if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            //tinygl_draw_line (tinygl_point (0, (3+paddlex)), tinygl_point (0, (5+paddlex)),1);
            return paddlex + 1;
        }
        
      
        
        if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
            //tinygl_draw_line (tinygl_point (0, (1+paddlex)), tinygl_point (0, (3+paddlex)),1);
            return paddlex - 1;
        }
        return paddlex;
}

void padmain (void)
{
   tinygl_init (10000);
   navswitch_init();
   int count = 0;

   tinygl_draw_line (tinygl_point (4, 2), tinygl_point (4, 4),1);

   while (1)
   {
       //pacer_wait ();
       tinygl_update();
       navswitch_update();
       
       if(navswitch_push_event_p(NAVSWITCH_SOUTH) && count < 2) {
            tinygl_clear();
            tinygl_draw_line (tinygl_point (4, (3+count)), tinygl_point (4, (5+count)),1);
            tinygl_update();
            count++;
        }
        
      
        
        if(navswitch_push_event_p(NAVSWITCH_NORTH) && count > -2) {
            tinygl_clear();
            tinygl_draw_line (tinygl_point (4, (1+count)), tinygl_point (4, (3+count)),1);
            tinygl_update();
            count--;
        }
   }
   
}
