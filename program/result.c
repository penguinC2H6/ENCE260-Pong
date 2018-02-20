/**  @file   result.c
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  game final result display 
*/
#include "result.h"
#include "program_control.h"
#include "system.h"
#include "tinygl.h"
#include "led.h"
#include "../fonts/font3x5_1.h"

#define TICK_MAX 2000

/** tick for result show time */
static int tick;

/** Initialise result  */
void result_init(void){
    
    tick = 0;
    led_init();
    led_set(LED1, 0);
    
    //display hardware initialize
    tinygl_init(RESULT_DISPLAY_TASK_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set (RESULT_MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    
    //choose display message
    if(GameResult == WIN){
        tinygl_text(" WIN");
    }
    else{
        tinygl_text(" LOSE");
    }
}
/** display task
    @param data not used in this function  */
void result_display_task(__unused__ void* data){
    if(tick < TICK_MAX){
        tinygl_update();
        tick++;
    }
    else{
        ProgramState = TITLE;
    }
}
/** led task, led flashing if win
    @param data not used in this function  */
void result_led_task(__unused__ void* data){
    if(GameResult == WIN){
        led_set(LED1,tick%2);
    }
    
}







