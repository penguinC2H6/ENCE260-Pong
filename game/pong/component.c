/**  @file   component.h
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  Components(ball, paddle) used by game pong.
             this file is built based on boing.c
*/

#include "system.h"
#include "component.h"

/** Initialise the state of a ball
    @param xstart x coordinate to start at
    @param ystart y coordinate to start at
    @param dir initial direction
    @param state initial state of ball
    @return ball.  */
ball_t ball_init (uint8_t x, uint8_t y, ball_dir_t dir, ball_state_t state)
{
    ball_t ball;

    if (x > SCREEN_WIDTH)
        x = SCREEN_WIDTH - 1;
    if (y > SCREEN_WIDTH)
        y = SCREEN_WIDTH - 1;

    ball.pos.x = x;
    ball.pos.y = y;
    ball.dir = dir;
    ball.state = state;

    return ball;
}

/** Update the state of a ball bouncing off the edges of the display
    @param state current state
    @return new state.  */
ball_t ball_wall_update (ball_t ball)
{
    tinygl_point_t hops[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1},
                             {0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
                             {0, 0}};

    ball.pos.x += hops[ball.dir].x;
    ball.pos.y += hops[ball.dir].y;
    
    if (ball.pos.x > SCREEN_WIDTH - 1 || ball.pos.x < 0 )
    {
        ball_dir_t newdir[] = {DIR_N, DIR_NW, DIR_W, DIR_SW,
                                DIR_S, DIR_SE, DIR_E, DIR_NE,
                                DIR_NO};
                                
        ball.pos.x -= 2 * hops[ball.dir].x;
        ball.dir = newdir[ball.dir];
    }
    
    if (ball.pos.y > SCREEN_HEIGHT - 1)
    {
        ball.state = OUTSIDE;
    }  
    if (ball.pos.y < 0){
        ball.dir = DIR_NO;
        ball.state = TRY;
    }
    return ball;
}

/** Update the ball state from recived ball state from other player
    @param the ball in this screen
    @param the x pos got from opposite player
    @param the ball dir got from opposite player */
void ball_new_screen_update(ball_t* ball, uint8_t x_recv, ball_dir_t dir_recv){
    
    ball->pos.x = SCREEN_WIDTH - x_recv - 1;
    ball->pos.y = SCREEN_HEIGHT - 1;
    
    if (dir_recv == DIR_N)
        ball->dir = DIR_S;
    else if(dir_recv == DIR_NE)
        ball->dir = DIR_SW;
    else if(dir_recv == DIR_NW)
        ball->dir = DIR_SE;
    
    ball->state = INSIDE;
    
}

/** Calculate ball position for display
    @param the ball in this screen
    @return the new ball for display    */
ball_t ball_for_display(ball_t ball){
    
    uint8_t tmp = ball.pos.x;
    ball.pos.x = SCREEN_HEIGHT -1 - ball.pos.y;
    ball.pos.y = SCREEN_WIDTH - 1 - tmp;
    
    return ball;
}

/** Reverse the direction of a ball
    @param ball current ball
    @return new ball with direction reversed.  */
ball_t ball_reverse (ball_t ball)
{
    ball_dir_t newdir[] = {DIR_S, DIR_SW, DIR_W, DIR_NW,
                            DIR_N, DIR_NE, DIR_E, DIR_SE,
                            DIR_NO};    

    ball.dir = newdir[ball.dir];
    return ball;
}

/** update the ball dir when ball hit horizontal object
    @param ball current ball
    @return new ball after hit horizontal object.  */
ball_t ball_bounce_horizontal(ball_t ball)
{
    ball_dir_t newdir[] = {DIR_S, DIR_SE, DIR_E, DIR_NE,
                            DIR_N, DIR_NW, DIR_W, DIR_SW,
                            DIR_NO};    

    ball.dir = newdir[ball.dir];
    return ball;
}

/** update the ball dir when ball hit vertical object
    @param ball current ball
    @return new ball after hit vertical object.  */
ball_t ball_bounce_vertical(ball_t ball)
{
    ball_dir_t newdir[] = {DIR_N, DIR_NW, DIR_W, DIR_SW,
                            DIR_S, DIR_SE, DIR_E, DIR_NE, 
                            DIR_NO};    

    ball.dir = newdir[ball.dir];
    return ball;
}

/** Initialise the state of a paddle
    @param x coordinate of right hand side of the paddle
    @return paddle.  */
paddle_t paddle_init(uint8_t xlhs, uint8_t y){
    
    paddle_t paddle;
    
    if (xlhs > SCREEN_WIDTH - PADDLE_LENGTH)
        paddle.xlhs = SCREEN_WIDTH - PADDLE_LENGTH;
    else 
        paddle.xlhs = xlhs;
        
    if (y >= SCREEN_HEIGHT)
        paddle.y = SCREEN_HEIGHT - 1;
    else
        paddle.y = y;
        
    return paddle;
    
}

/** Update the state of paddle depending on screen edge and ball
    @param paddle
    @param paddle dir
    @param the ball in the screen  */
void paddle_update(paddle_t* paddle, paddle_dir_t dir, const ball_t* ball){
    
    paddle_t newPaddle;
    
    if (dir == P_DIR_N && paddle->y < SCREEN_HEIGHT - 3){
        newPaddle.xlhs  = paddle->xlhs;
        newPaddle.y  = paddle->y + 1;
        if (!paddle_ball_collision_detect(&newPaddle, ball))
            paddle->y++;
    } 
    else if (dir == P_DIR_S && paddle->y != 0){
        newPaddle.xlhs  = paddle->xlhs;
        newPaddle.y  = paddle->y - 1;
        if (!paddle_ball_collision_detect(&newPaddle, ball))
            paddle->y--;
    }       
    else if (dir == P_DIR_W && paddle->xlhs != 0){
        newPaddle.xlhs  = paddle->xlhs - 1;
        newPaddle.y  = paddle->y;
        if (!paddle_ball_collision_detect(&newPaddle, ball))
            paddle->xlhs--;
    }
    else if (dir == P_DIR_E && (paddle->xlhs + PADDLE_LENGTH) < SCREEN_WIDTH){
        newPaddle.xlhs  = paddle->xlhs + 1;
        newPaddle.y  = paddle->y;
        if (!paddle_ball_collision_detect(&newPaddle, ball))
            paddle->xlhs++;
    }
        
}

/** Update the state of paddle for display
    @param paddle
    @return paddle for display  */
paddle_t paddle_for_display(paddle_t paddle){
    
    uint8_t tmp = paddle.xlhs;
    paddle.xlhs = SCREEN_HEIGHT - 1 - paddle.y;
    paddle.y = SCREEN_WIDTH - 1 - tmp;
    
    return paddle;
}

/** check ball and paddle collision
    @param paddle
    @param ball
    @return whether collision detected  */
bool paddle_ball_collision_detect(const paddle_t* paddle, const ball_t* ball){
    
    if (ball->pos.y == paddle->y && ball->pos.x >= paddle->xlhs && ball->pos.x < paddle->xlhs + PADDLE_LENGTH)
        return true;
    return false;
    
}






