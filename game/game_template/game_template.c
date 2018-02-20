#include "game_template.h"
#include "program_control.h"

#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "led.h"
#include "../fonts/font3x5_1.h"

void game_template_init(void){
    
    tinygl_init(DISPLAY_TASK_RATE);
    navswitch_init ();
    ir_uart_init();
    button_init();
    
    led_init();
    led_set(LED1, 0);
    
    if (PlayerType == MASTER){}
    else if(PlayerType == SLAVE){}
    else{}
    
}


void game_template_display_task(__unused__ void* data){}

void game_template_send_task(__unused__ void* data){}
void game_template_recv_task(__unused__ void* data){}





