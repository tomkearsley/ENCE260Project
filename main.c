#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "ball.h"
#include "paddle.h"
#include "ir_uart.h"
#define GAMESPEED 2     // constant between 1 and 10 for game speed
#define PACERSPEED 500


  
typedef enum {XPOS, YVEL} tx_message_t;

typedef enum {SEND_XPOS, SEND_YVEL} tx_state_t;


int main (void)
{    
    
    system_init();
    tinygl_init(PACERSPEED);
    pacer_init(PACERSPEED);
    navswitch_init ();
    ir_uart_init();
    
    ball pongball = {0,1,2,1,0,0};
    
    int count = 0;
    int paddlex = 3;
    
    while (1)
    {
        
        navswitch_update();
        paddlex = paddlecheck(paddlex);
        
        tinygl_update();
        tinygl_clear();
        
        
        tinygl_draw_line (tinygl_point (0, paddlex - 1), tinygl_point (0, paddlex+1),1);
        tinygl_draw_point (tinygl_point(pongball.ballx,pongball.bally), 1);
        
        pacer_wait();
        
        if (count >= 300/GAMESPEED) {//tick
            count = 0;
            pongball = checkball(pongball,paddlex);
        }
        count ++;
        
        if(pongball.balloffscreen == 1) {
            static uint8_t state = SEND_XPOS;

            /* Alternately, send x position and y position messages.  */
            switch (state)
            {
            case SEND_XPOS:
                ir_uart_putc (pongball.bally & 0x0f);
                state = SEND_YVEL;
                break;

            case SEND_YVEL:
                ir_uart_putc (pongball.bally_velocity & 0x0f);
                state = SEND_XPOS;
                break;
            }
            
            
            
            uint8_t c;
            c = ir_uart_getc ();
            
            

            /* Decode the received message.  */
            switch (c >> 4)
            {
            case XPOS:
                pongball.bally = c & 0x0f;
                break;

            case YVEL:
                pongball.bally_velocity = c & 0x0f;
                break;
            }
            pongball.ballx = 0;
            
            
        }
            
            
        }
        
}
