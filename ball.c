/**
 * @file ball.c
 * @authors Gavin Mcgill gmc132 59048032
 * @date 16/Oct/2017
 * basic ball mechanics that controll what direction the ball moves and if the ball is to collide with anything
 * */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define speed 5     // constant between 1 and 10 for game speed
#define SCREEN_LENGTH 6
#define PADDLE_ROW 4
// Structure for pong ball.
typedef struct ball_s {
    int ballx;
    int ballx_velocity;
    int bally;
    int bally_velocity;
    int balloffscreen; // 0 = onscreen 1  = offscreen
    int tick_count;
}ball;

/**
 * Checks for collision between ball and paddle and changes
 * balls direction appropriately.
 * @param gameball of structure ball, the current ball in the game.
 * @param paddlex is the current location of the paddle (center pixel)
 * @return gameball with updated velocity and direction
 * */
ball paddleCollision(ball gameball,int paddlex) {
        
    //moving towards switch
    if (gameball.ballx_velocity == 1) {
        if (gameball.ballx > 4) {//bounce of bottom wall
            gameball.ballx_velocity = -1;
        }
        
        // paddle collisions
        if (gameball.ballx == (PADDLE_ROW - 1)) { //Ball is 1 pixel Above paddle.
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
    return gameball;

}


/**
 * Used in main. Runs both the paddleCollision and ballMovement functions
 * @param gameball is a struct of type ball_s, used in the current game.
 * @param paddlex is the current position of the paddle.
 * @return gameball after it has been checked for collision and location
 * has been changed.
 * **/
ball checkball(ball gameball,int paddlex){
    ball gameball = paddleCollision(gameball,paddlex);
    ball gameball = ballMovement(gameball);

    
    return gameball;
}

/**
 * Updates the location of the ball based on boundaries
 * @param Current ball structure used for the game.
 * @return Ball with updated velocity and direction.
 * */
ball ballMovement(ball gameball) {
    
    if (gameball.bally_velocity == 1) {
        if (gameball.bally < SCREEN_LENGTH) {
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
    // 1 = Ball IS off screen.
    if (gameball.balloffscreen == 1) {
        gameball.tick_count++;
        if (gameball.tick_count > SCREEN_LENGTH){
            gameball.balloffscreen = 0; //Ball is set to NOT offscreen
            gameball.ballx = -1;
            gameball.ballx_velocity = 1;
            gameball.ballx += gameball.ballx_velocity;
        }
    }
    return gameball;
}
