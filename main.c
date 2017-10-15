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
    navswitch_init();
    ir_uart_init();
    
    ball pongball = {0,1,2,1,0,0};
    
    int count = 0;
    int paddlex = 3;
    int stage = 0;
    
    while (1)
    {
        
        navswitch_update();
        paddlex = paddlecheck(paddlex);
        
        tinygl_update();
        tinygl_clear();
        
        if (stage == 0){
            tinygl_draw_line (tinygl_point (4, paddlex - 1), tinygl_point (4, paddlex+1),1);
            tinygl_draw_point (tinygl_point(pongball.ballx,pongball.bally), 1);
            
            pacer_wait();
            
            if (count >= 300/GAMESPEED) {//tick
                count = 0;
                pongball = checkball(pongball,paddlex);
            }
            count ++;
            
            
            
            if(pongball.balloffscreen == 1) {

                /* Alternately, send x position and y position messages.  */
                ir_uart_putc (pongball.bally);
                ir_uart_putc (pongball.bally_velocity);
                pongball.balloffscreen = 0;
                pongball.ballx_velocity = 1;
                pongball.ballx = 0;
                
                                  
                uint8_t c;
                uint8_t y;

                    c = ir_uart_getc ();
                    y = ir_uart_getc ();
                    pongball.bally = 6-c;
                    pongball.bally_velocity = y;
                    pongball.ballx = 0;
                    pongball.ballx_velocity = 1;
                    pongball.balloffscreen = 0;
                
            
                
            }
               
                
                
                
                

               
                
            }
        }
            
            
        }
        
}
