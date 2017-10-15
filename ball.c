#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define speed 5     // constant between 1 and 10 for game speed

typedef struct ball_s {
    int ballx;
    int ballx_velocity;
    int bally;
    int bally_velocity;
    int balloffscreen;
    int tick_count;
}ball;

ball checkball(ball gameball,int paddlex){
    
    
    //moving towards switch
    if (gameball.ballx_velocity == 1) {
        if (gameball.ballx > 3) {//bounce of bottom wall
            gameball.ballx_velocity = -1;
        }
        
        // paddle collisions
        if (gameball.ballx == 3) {
            if (paddlex == (gameball.bally + gameball.bally_velocity)) {
                gameball.ballx_velocity = -1;
            } else if (paddlex + 1 == (gameball.bally + gameball.bally_velocity)) {
                gameball.ballx_velocity = -1;
            } else if (paddlex - 1 == (gameball.bally + gameball.bally_velocity)) {
                gameball.ballx_velocity = -1;
            }
        }
        
        
        
        gameball.ballx += gameball.ballx_velocity;
        
        
    //moving towards IR
    }else if (gameball.ballx_velocity == -1){
        
        if (gameball.ballx >= 0) {
            gameball.ballx += gameball.ballx_velocity;
            
        } else {//if ball leaves screen
            if(gameball.balloffscreen == 0){
                gameball.tick_count = 0;
            }
            gameball.balloffscreen = 1;
            
        }
    }
    
    
    // left/right movement
    
    if (gameball.bally_velocity == 1) {
        if (gameball.bally < 6) {
            gameball.bally += gameball.bally_velocity;
        } else {
            gameball.bally_velocity = -1;
            gameball.bally += gameball.bally_velocity;
        }
    }else if (gameball.bally_velocity == -1){
        if (gameball.bally < 1) {
            gameball.bally_velocity = 1;
        }
        gameball.bally += gameball.bally_velocity;
    }
    
    if (gameball.balloffscreen == 1) {
        gameball.tick_count ++;
        if (gameball.tick_count > 10){
            gameball.balloffscreen = 0;
            gameball.ballx = -1;
            gameball.ballx_velocity = 1;
            gameball.ballx += gameball.ballx_velocity;
        }
    }
    return gameball;
}
