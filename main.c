#include "system.h"
#include "pio.h"

/* Include the pacer module from the previous lab.
   You must have completed this before starting this lab2-exercise.  */
#include "pacer.h"

#define LED_PIO PIO_DEFINE (PORT_C, 2)
#define speed 15     // constant between 1 and 100 for game speed

static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

int main (void)
{
    system_init ();
    
    /* TODO: Initialise the pins of the LED matrix.  */
    pio_config_set(LEDMAT_COL1_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL2_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL3_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL4_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL5_PIO,PIO_OUTPUT_HIGH);
    
    pio_config_set(LEDMAT_ROW1_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW2_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW3_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW4_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW5_PIO,PIO_OUTPUT_HIGH); 
    pio_config_set(LEDMAT_ROW6_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW7_PIO,PIO_OUTPUT_HIGH); 
    

    /* Set up pacer with a frequency of 50 Hz.  */
    pacer_init (50);
    
    int count = 0;
    int tick_count = 0;
    int ballx = 0;
    int ballx_velocity = 1;
    int bally = 2;
    int bally_velocity = 1;
    int balloffscreen = 0;
    
    int r;
    int c;

    while (1)//each loop is 100 ms
    {
        /* Pace the loop.  */
                
        pacer_wait ();
        
        //replace with for loop
        
        for (c = 0; c < 5; c++) {
            pio_output_high(cols[c]);
        }

        for (r = 0; r < 7; r++) {
            pio_output_high(rows[r]);
        }
        
        
        pio_output_low(cols[ballx]);
        pio_output_low(rows[bally]);

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
}
