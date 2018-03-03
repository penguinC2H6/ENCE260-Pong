/**  @file   title.c
     @author Wen yu wyu18
     @brief  game title display 
*/
#include "title.h"
#include "program_control.h"
#include "system.h"
#include "button.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "led.h"
#include "../fonts/font3x5_1.h"

#define INITIAL_MESSAGE 'A'
#define START_MESSAGE 'B'

/** title display stage */
typedef enum{
    INITIAL,
    START
} TitleStage;

/**  create title stage variable*/
static TitleStage titleStage;

/** Initialise title  */
void title_init(void){
    
    titleStage = INITIAL;
    
    //hardware initial
    navswitch_init();
    button_init();
    ir_uart_init();
    led_init();
    led_set(LED1, 0);
    
    tinygl_init(TITLE_DISPLAY_TASK_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set (TITLE_MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text(" PONG!");
    
}
/** display task
    @param data not used in this function  */
void title_display_task(__unused__ void* data){
    tinygl_update();
}
/** navswitch task
    @param data not used in this function  */
void title_navswitch_task(__unused__ void* data) {
    
    navswitch_update();
    
    if (navswitch_push_event_p(NAVSWITCH_PUSH)){
        titleStage = START;
        led_set(LED1, 0);
        //set player as master
        PlayerType = MASTER;
        tinygl_clear();
    }
}
/** ir send task
    @param data not used in this function  */
void title_send_task(__unused__ void* data){
    if(titleStage == INITIAL){
    }
    else if(titleStage == START){
        ir_uart_putc (START_MESSAGE);
        //set whole program to game state
        ProgramState = GAME;
    }
}
/** ir receive task
    @param data not used in this function  */
void title_recv_task(__unused__ void* data) {
    
    if (ir_uart_read_ready_p()) {
        if(ir_uart_getc() == START_MESSAGE){
            titleStage = START;
            tinygl_clear();
            //set player as slave
            PlayerType = SLAVE;
            //set whole program to game state
            ProgramState = GAME;
        }
    }
    
}






