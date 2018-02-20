/**  @file   pong.h
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  game pong. A traditional pong game with paddle vertical movement
*/

#ifndef PONG_H
#define PONE_H

#include "system.h"

/** display task rate in HZ */
#define PONG_DISPLAY_TASK_RATE 500
/** ball task rate in HZ, this define the ball move speed */
#define PONG_BALL_TASK_RATE 5
/** paddle task rate in HZ */
#define PONG_PADDLE_TASK_RATE 50
/** button task rate in HZ */
#define PONG_BUTTON_TASK_RATE 100
/** ir send task rate in HZ */
#define PONG_SEND_TASK_RATE 5
/** ir receive task rate in HZ */
#define PONG_RECV_TASK_RATE 50
/** led task rate in HZ */
#define PONG_LED_TASK_RATE 100


/** Initialise game  */
void pong_init(void);
/** display task
    @param data not used in this function  */
void pong_display_task(__unused__ void* data);
/** ball location and interaction task
    @param data not used in this function  */
void pong_ball_task(__unused__ void* data);
/** paddle location and interaction task
    @param data not used in this function  */
void pong_paddle_task(__unused__ void* data);
/** ir send task
    @param data not used in this function  */
void pong_send_task(__unused__ void* data);
/** ir receive task
    @param data not used in this function  */
void pong_recv_task(__unused__ void* data);


#endif 
