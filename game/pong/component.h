/**  @file   component.h
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  Components(ball, paddle) used by game pong
*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include "tinygl.h"

/** define screen width */
#define SCREEN_WIDTH TINYGL_HEIGHT
/** define screen height */
#define SCREEN_HEIGHT TINYGL_WIDTH
/** define paddle length */
#define PADDLE_LENGTH 3


/** Compass direction of ball.  */
typedef enum {
    DIR_N, DIR_NE, DIR_E, DIR_SE,
    DIR_S, DIR_SW, DIR_W, DIR_NW, DIR_NO
} ball_dir_t;
/** Compass direction of paddle.  */
typedef enum {
    P_DIR_N, P_DIR_E, P_DIR_S, P_DIR_W, P_DIR_NO
} paddle_dir_t;
/** Ball state.  */
typedef enum {
    INSIDE, OUTSIDE, TRY
} ball_state_t;


/** Structure defining ball of ball.  */
typedef struct ball_s {
    tinygl_point_t pos; 
    ball_dir_t dir;
    ball_state_t state;
} ball_t;
/** Structure defining paddle of paddel.  */
typedef struct paddle_s {
    uint8_t xlhs;
    uint8_t y;
} paddle_t;



/** Initialise the state of a ball
    @param xstart x coordinate to start at
    @param ystart y coordinate to start at
    @param dir initial direction
    @param state initial state of ball
    @return ball.  */
ball_t ball_init (uint8_t x, uint8_t y, ball_dir_t dir, ball_state_t state);

/** Update the state of a ball bouncing off the edges of the display
    @param state current state
    @return new state.  */
ball_t ball_wall_update (ball_t ball);

/** Update the ball state from recived ball state from other player
    @param the ball in this screen
    @param the x pos got from opposite player
    @param the ball dir got from opposite player */
void ball_new_screen_update(ball_t* ball, uint8_t x_recv, ball_dir_t dir_recv);

/** Calculate ball position for display
    @param the ball in this screen
    @return the new ball for display */
ball_t ball_for_display(ball_t ball);

/** Reverse the direction of a ball
    @param ball current ball
    @return new ball with direction reversed.  */
ball_t ball_reverse (ball_t ball);

/** update the ball dir when ball hit horizontal object
    @param ball current ball
    @return new ball after hit horizontal object.  */
ball_t ball_bounce_horizontal(ball_t ball);

/** update the ball dir when ball hit vertical object
    @param ball current ball
    @return new ball after hit vertical object.  */
ball_t ball_bounce_vertical(ball_t ball);

/** Initialise the state of a paddle
    @param x coordinate of right hand side of the paddle
    @return paddle.  */
paddle_t paddle_init(uint8_t xlhs, uint8_t y);

/** Update the state of paddle depending on screen edge and ball
    @param paddle
    @param paddle dir
    @param the ball in the screen  */
void paddle_update(paddle_t* paddle, paddle_dir_t dir, const ball_t* ball);

/** Update the state of paddle for display
    @param paddle
    @return paddle for display  */
paddle_t paddle_for_display(paddle_t paddle);

/** check ball and paddle collision
    @param paddle
    @param ball
    @return whether collision detected  */
bool paddle_ball_collision_detect(const paddle_t* paddle, const ball_t* ball);




#endif
