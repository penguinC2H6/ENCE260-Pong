/**  @file   result.h
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  game final result display 
*/
#ifndef RESULT_H
#define RESULT_H

#include "system.h"

/** display task rate in HZ */
#define RESULT_DISPLAY_TASK_RATE 500
/** message display task rate in HZ */
#define RESULT_MESSAGE_RATE 25
/** led task rate in HZ */
#define RESULT_LED_TASK_RATE 55

/** Initialise result  */
void result_init(void);
/** display task
    @param data not used in this function  */
void result_display_task(__unused__ void* data);
/** led task, led flashing if win
    @param data not used in this function  */
void result_led_task(__unused__ void* data);



#endif 
