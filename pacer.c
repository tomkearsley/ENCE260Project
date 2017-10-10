#include <avr/io.h>
#include "pacer.h"


static uint16_t pacer_period;

/* Initialise the pacer module.  */
void pacer_init (uint16_t pacer_frequency)
{
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    pacer_period = pacer_frequency;
}


/* Pace a while loop.  */
void pacer_wait (void)
{

    /* TODO: Calculate the timer/counter value needed 
       for the given number of milliseconds. */
       int waittime = pacer_period;
    
    /* TODO: Wait for the timer/couter to reach the 
       value calculated above.  */
        
        while (TCNT1 < waittime) {
            continue;
        }
        TCNT1 = 0;
}
