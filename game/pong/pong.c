/**  @file   pong.c
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  game pong. A traditional pong game with paddle vertical movement
*/

#include "pong.h"
#include "program_control.h"
#include "component.h"
#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "led.h"


#define ON 1
#define OFF 0

/** ir message type */
typedef enum {BALL, FAIL} tx_type_t;
/** create a ball */
static ball_t Ball;	
/** create a paddle */
static paddle_t Paddle;	
/** ir message sended */
static bool sended;

/** draw paddle in the screen
    @param show paddle on/off  */
void draw_paddle(bool show){
    
    paddle_t p = paddle_for_display(Paddle);
    tinygl_point_t lhs, rhs;
    lhs.x = p.xlhs;
    lhs.y = p.y;
    rhs.x = p.xlhs;
    rhs.y = p.y - PADDLE_LENGTH + 1;
    
    tinygl_draw_line(lhs, rhs, show);
}
/** draw ball in the screen
    @param show paddle on/off  */
void draw_ball(bool show){
    
    if (!show || Ball.state != INSIDE)
        tinygl_draw_point(ball_for_display(Ball).pos, OFF);
    else
        tinygl_draw_point(ball_for_display(Ball).pos, ON);
}

/** Initialise game  */
void pong_init(void){
    
    //Iniialize hardware
    tinygl_init(PONG_DISPLAY_TASK_RATE);
    navswitch_init ();
    ir_uart_init();
    button_init();
    
    led_init();
    led_set(LED1, 0);
    
    //Initialize Master player
    if (PlayerType == MASTER){
        Ball = ball_init(3, 1, DIR_NE, INSIDE);
        draw_ball(true);
        sended = false;
    }
    //Initialize slave player
    else{
        Ball = ball_init(0, 0, DIR_NO, OUTSIDE);
        sended = true;
    }
    
    //Initialize paddle
    Paddle.xlhs = 2;
    Paddle.y = 0;
    draw_paddle(ON);
    
}
/** display task
    @param data not used in this function  */
void pong_display_task(__unused__ void* data){
    tinygl_update();
}
/** ball location and interaction task
    @param data not used in this function  */
void pong_ball_task(__unused__ void* data){
    
    //the ball is inside the screen
    if(Ball.state == INSIDE){
        draw_ball(false);
    
        ball_t tmp = Ball;
        Ball = ball_wall_update(Ball);
        if(paddle_ball_collision_detect(&Paddle, &Ball)){
            Ball = tmp;
            Ball = ball_bounce_horizontal(Ball);
            Ball = ball_wall_update(Ball);
        }
        draw_ball(true);
        
    }
    
    //the ball is outside the screen
    else if (Ball.state == OUTSIDE && !sended){
        led_set(LED1,1);
        ir_uart_putc ((BALL << 7) | (Ball.pos.x << 4) | (Ball.dir & 0x0f));
        sended = true;
    }
    // ball try
    else if(Ball.state == TRY){
        led_set(LED1,1);
        ir_uart_putc ((FAIL << 7));
       
       
       ProgramState = RESULT;
    }
    led_set(LED1, OFF);
    
}
/** paddle location and interaction task
    @param data not used in this function  */
void pong_paddle_task(__unused__ void* data){
    
    navswitch_update ();
    button_update();
    
    //paddle control
    if (navswitch_push_event_p (NAVSWITCH_EAST)){
        draw_paddle(false);
        paddle_update(&Paddle, P_DIR_S, &Ball);
        draw_paddle(true);
    }
    else if (navswitch_push_event_p (NAVSWITCH_WEST)){
        draw_paddle(false);
        paddle_update(&Paddle, P_DIR_N, &Ball);
        draw_paddle(true);
    }
    else if (navswitch_push_event_p (NAVSWITCH_NORTH)){
        draw_paddle(false);
        paddle_update(&Paddle, P_DIR_E, &Ball);
        draw_paddle(true);
    }
    else if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
        draw_paddle(false);
        paddle_update(&Paddle, P_DIR_W, &Ball);
        draw_paddle(true);
    }
    //game reset
    else if (button_push_event_p(BUTTON1)){
        ProgramState = TITLE;
    }
}
/** ir send task
    @param data not used in this function  */
void pong_send_task(__unused__ void* data){
}
/** ir receive task
    @param data not used in this function  */
void pong_recv_task(__unused__ void* data){
    
    char c;
    if(Ball.state == OUTSIDE && sended){
        led_set(LED1,1);
        if (ir_uart_read_ready_p ()){
            c = ir_uart_getc ();
        
            //if ball position message
            if((c >> 7)== BALL){
                    ball_new_screen_update(&Ball, ((c & 0x70)>>4), (c&0x0f));
                    Ball = ball_wall_update(Ball);
                    ball_t b = ball_for_display(b);
                    draw_ball(true);
                    sended = false;
            }
            //if opposite player fail message
            else{
                GameResult = WIN;
                ProgramState = RESULT;
            }
        }
        led_set(LED1,0);
    }
    
}








