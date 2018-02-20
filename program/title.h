/**  @file   title.h
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  game title display 
*/

#ifndef TITLE_H
#define TITLE_H

#include "system.h"

/** display task rate in HZ */
#define TITLE_DISPLAY_TASK_RATE 500
/** message scorll rate in HZ */
#define TITLE_MESSAGE_RATE 25
/** navswitch task rate in HZ */
#define TITLE_NAVSWITCH_TASK_RATE 100
/** ir send task rate in HZ */
#define TITLE_SEND_TASK_RATE 10
/** ir receive task rate in HZ */
#define TITLE_RECV_TASK_RATE 50

/** Initialise title  */
void title_init(void);
/** display task
    @param data not used in this function  */
void title_display_task(__unused__ void* data);
/** navswitch task
    @param data not used in this function  */
void title_navswitch_task(__unused__ void* data);
/** ir send task
    @param data not used in this function  */
void title_send_task(__unused__ void* data);
/** ir receive task
    @param data not used in this function  */
void title_recv_task(__unused__ void* data);


#endif 
