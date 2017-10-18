/**
 * @file paddle.c
 * @author Thomas Kearsley tke29 98112573
 * @date 14/10/17
 * Simple paddle for pong game. Paddle controled using navswitch.
 * */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pio.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define REFRESH_RATE 10000
#define PADDLE_ROW 4
#define COUNT_MAX 2
#define COUNT_MIN -2

/**
 * If paddle is being moved left or right the function 
 * returns the new position of the paddle.
 * @param Current position of paddle
 * @return New paddle position
 * **/
int paddlecheck(int paddlex){
    
        if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            return paddlex + 1;
        }
        
      
        
        if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
            return paddlex - 1;
        }
        return paddlex;
}
/**
 * Creates the initial paddle and allows user to update its position
 * based on navswitch movement.
 * **/
void padmain (void)
{
   tinygl_init (REFRESH_RATE);
   navswitch_init();
   int count = 0;
   //Initial position of paddle. Center of bottom row of screen.
   tinygl_draw_line (tinygl_point (PADDLE_ROW, 2), tinygl_point (PADDLE_ROW, 4),1);

   while (1)
   {
       tinygl_update();
       navswitch_update();
       //COUNT_MAX ensures paddle does not go off the screen to the right
       if(navswitch_push_event_p(NAVSWITCH_SOUTH) && count < COUNT_MAX) {
            tinygl_clear();
            tinygl_draw_line (tinygl_point (4, (3+count)), tinygl_point (4, (5+count)),1);
            tinygl_update();
            count++;
        }
        
      
        //COUNT_MIN ensures paddle does not go off the screen to the left
        if(navswitch_push_event_p(NAVSWITCH_NORTH) && count > COUNT_MIN) {
            tinygl_clear();
            tinygl_draw_line (tinygl_point (4, (1+count)), tinygl_point (4, (3+count)),1);
            tinygl_update();
            count--;
        }
   
   }
   
   
   
}
