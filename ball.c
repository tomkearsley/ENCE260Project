#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define speed 5     // constant between 1 and 10 for game speed

struct ball {
    int ballx = 0;
    int ballx_velocity = 1;
    int bally = 2;
    int bally_velocity = 1;
    int balloffscreen = 0;
}ball;


int runball (void)
{

    system_init();
    tinygl_init (PACER_RATE);
    pacer_init (PACER_RATE);
    
    int count = 0;
    int tick_count = 0;
    
    while(1)
    {
        tinygl_update ();
        tinygl_clear();
        tinygl_draw_point (tinygl_point(ballx,bally), 1);
        pacer_wait();
        
        if (count >= 300/speed) {//tick
            count = 0;
            
            if (ballx_velocity == 1) {
                if (ballx < 5) {
                    ballx += ballx_velocity;
                    
                } else {// condition if ball leaves screen
                    if(balloffscreen == 0){
                        tick_count = 0;
                    }
                    balloffscreen = 1;
                }
            }else if (ballx_velocity == -1){
                if (ballx < 1) {
                    ballx_velocity = 1;
                }
                ballx += ballx_velocity;
            }
            
            if (bally_velocity == 1) {
                if (bally < 6) {
                    bally += bally_velocity;
                } else {
                    bally_velocity = -1;
                    bally += bally_velocity;
                }
            }else if (bally_velocity == -1){
                if (bally < 1) {
                    bally_velocity = 1;
                }
                bally += bally_velocity;
            }
            
            if (balloffscreen == 1) {
                tick_count ++;
                if (tick_count > 8){
                    balloffscreen = 0;
                    ballx = 5;
                    ballx_velocity = -1;
                    ballx += ballx_velocity;
                }
            }
            
        }
        
        count ++;
    }
    return 0;
}
