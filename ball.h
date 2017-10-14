#ifndef BALL_H
#define BALL_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

/* Initialise the pacer module.  */
typedef struct ball_s {
    int ballx;
    int ballx_velocity;
    int bally;
    int bally_velocity;
    int balloffscreen;
    int tick_count;
}ball;


/* Pace a while loop.  */
ball checkball(ball gameball,int paddlex);

#endif //PACER_H
