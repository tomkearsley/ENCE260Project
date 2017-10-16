#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "ball.h"
#include "paddle.h"
#include "ir_uart.h"

#define GAMESPEED 1     // constant between 1 and 10 for game speed
#define PACERSPEED 500

#define PACER_RATE 500
#define MESSAGE_RATE 30
#define LOOP_RATE 500


  
typedef enum {XPOS, YVEL} tx_message_t;

typedef enum {SEND_XPOS, SEND_YVEL} tx_state_t;

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int main (void)
{    
    
    system_init();
    tinygl_init(PACERSPEED);
    pacer_init(PACERSPEED);
    navswitch_init();
    ir_uart_init();
    
     /* TODO: Initialise tinygl. */
    tinygl_init(LOOP_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);

    /* TODO: Set the message using tinygl_tlab3-ext().  */
    tinygl_text("PONG PRESS NAVSWITCH TO START\0");
    //tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    

    pacer_init (PACER_RATE);
    
    int menu = 0;
    char player = 'O';
    
    //choose who is what player
    while(menu == 0)
    {
        pacer_wait();
        
        /* TODO: Call the tinygl update function. */
        tinygl_update();
        navswitch_update();
        if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('T');
            menu = 1;
            player = 'O';
            break;
        }
        if (ir_uart_read_ready_p ()) {
            player = ir_uart_getc();
            if (player == 'T') {
                menu = 1;
                break;
            }
        }
        
    }
    
    //display what player you are
    display_character(player);
    int showtime = 0;
    while(showtime < 1000)
    {
        pacer_wait();
        
        /* TODO: Call the tinygl update function. */
        tinygl_update();
        navswitch_update();
        
        showtime ++;
        
    }
    
    ball pongball = {0,1,2,1,0,0};
    if (player == 'T') {
        pongball.ballx_velocity = 0;
        pongball.ballx = -1;
    }
    
    int count = 0;
    char win = 'N';
    int paddlex = 3;
    int stage = 0;
    int tick_count = 0;
    
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
            
            if (count >= 400/GAMESPEED) {//tick
                count = 0;
                pongball = checkball(pongball,paddlex);
                if (tick_count == 6  && player == 'T') {
                    pongball.ballx_velocity = 1;
                    pongball.ballx = 0;
                }
                tick_count ++;
            }
            count ++;
            
            if (ir_uart_read_ready_p ()) {
                win = ir_uart_getc();
                if (win == 'Y') {
                stage = 1;
                tinygl_clear();
                tinygl_font_set(&font5x7_1);
                tinygl_text_speed_set(2);
                tinygl_text("WINNER!\0");
                tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
                while(stage == 1) {
                    tinygl_update();
                    navswitch_update();
                    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
                        tinygl_clear();
                        pongball.ballx = 6;
                        stage = 0;
                    }
                }
                }
            }
            
            if((pongball.ballx == 5)) {
                ir_uart_putc('Y');
                stage = 1;
                tinygl_clear();
                tinygl_font_set(&font5x7_1);
                tinygl_text_speed_set(2);
                tinygl_text("LOOSER!\0");
                tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
                while(stage == 1) {
                    tinygl_update();
                    navswitch_update();
                    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
                        tinygl_clear();
                        pongball.ballx = 6;
                        stage = 0;
                    }
                }
            
            }
            }
            
            
        }
        tinygl_clear();
        tinygl_text("LOSE\0");
        tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
        
        
            
            
        
}
