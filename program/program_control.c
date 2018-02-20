/**  @file   program_control.c
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  this module controls the whole program. it switches the program 
             in the three stage: title, game, result. This module is built based 
             on task.c
*/

#include "program_control.h"
#include "system.h"
#include "timer.h"
#include "title.h"
#include "pong.h"
#include "result.h"

/** With 16-bit times the maximum value is 32768.  */
#define TASK_OVERRUN_MAX 32767

/** Task function prototype.  */
typedef void (*task_func_t)(void *data);
/** program initial function prototype  */
typedef void (*program_init_func_t)(void);
/** program function prototype  */
typedef void (*program_func_t)(void* data);
/** Task structure.  */
typedef struct task_struct
{
    /** Function to call.  */
    task_func_t func;
    /** Generic pointer to pass to function.  */
    void *data;
    /** How many ticks between scheduling events.  */
    timer_tick_t period;    
    /** When to reschedule.  */
    timer_tick_t reschedule;
} task_t;

/** Program state, Title,Game,Result  */
program_state_t ProgramState;
/** player type, master,slave or equal  */
player_type_t PlayerType;
/** final game result  */
game_result_t GameResult;
/** game score  */
score_t GameScore;

/** Schedule tasks
    @param tasks pointer to array of tasks (the highest priority
           task comes first)
    @param num_tasks number of tasks to schedule
    @return this never returns.
*/
void task_schedule (task_t *tasks, uint8_t num_tasks)
{
    uint8_t i;
    timer_tick_t now;
    task_t *next_task;
    
    program_state_t ps = ProgramState;

    timer_init ();
    now = timer_get ();

    /* Start by scheduling the first task.  */
    next_task = tasks;

    while (ps == ProgramState)
    {
        timer_tick_t sleep_min;

        /* Wait until the next task is ready to run.  */
        timer_wait_until (next_task->reschedule);

        /* Schedule the task.  */
        next_task->func (next_task->data);

        /* Update the reschedule time.  */
        next_task->reschedule += next_task->period;

        sleep_min = ~0;
        now = timer_get ();

        /* Search array of tasks.  Schedule the first task (highest priority)
           that needs to run otherwise wait until first task ready.  */
        for (i = 0; i < num_tasks; i++)
        {
            task_t * task = tasks + i;
            timer_tick_t overrun;

            overrun = now - task->reschedule;
            if (overrun < TASK_OVERRUN_MAX)
            {
                /* Have found a task that can run immediately.  */
                next_task = task;
                break;
            }
            else
            {
                timer_tick_t sleep;

                sleep = -overrun;
                if (sleep < sleep_min)
                {
                    sleep_min = sleep;
                    next_task = task;
                }
            }
        }
    }
}


/** title program inital */
void title_program_init(void){

    ProgramState = TITLE;
    PlayerType = EQUAL;
    GameResult = DRAW;
    GameScore.mine = 0;
    GameScore.player = 0;

    title_init();
}
/** assemble title tasks
    @param data not used in this function  */
void title_program(__unused__ void* data){
    
    task_t tasks[]=
    {
        {.func = title_display_task, .period = TASK_RATE/TITLE_DISPLAY_TASK_RATE},
        {.func = title_send_task, .period = TASK_RATE/TITLE_SEND_TASK_RATE},
        {.func = title_recv_task, .period = TASK_RATE/TITLE_RECV_TASK_RATE},
        {.func = title_navswitch_task, .period = TASK_RATE/TITLE_NAVSWITCH_TASK_RATE}
        
    };
    task_schedule(tasks, ARRAY_SIZE(tasks));
}

/** game inital */
void game_program_init(void){
    pong_init();
}
/** assemble game tasks
    @param data not used in this function  */
void game_program(__unused__ void* data){
    
    task_t tasks[]=
    {
        {.func = pong_display_task, .period = TASK_RATE/PONG_DISPLAY_TASK_RATE},
        {.func = pong_paddle_task, .period = TASK_RATE/PONG_PADDLE_TASK_RATE},
        {.func = pong_ball_task, .period = TASK_RATE/PONG_BALL_TASK_RATE},
        {.func = pong_recv_task, .period = TASK_RATE/PONG_RECV_TASK_RATE},
        {.func = pong_send_task, .period = TASK_RATE/PONG_RECV_TASK_RATE}
    };
    task_schedule(tasks, ARRAY_SIZE(tasks));
}

/** result inital */
void result_program_init(void){
    result_init();
}
/** assemble result tasks
    @param data not used in this function  */
void result_program(__unused__ void* data){
    
    task_t tasks[]=
    {
        {.func = result_display_task, .period = TASK_RATE/RESULT_DISPLAY_TASK_RATE},
        {.func = result_led_task, .period = TASK_RATE/RESULT_LED_TASK_RATE}
    };
    task_schedule(tasks, ARRAY_SIZE(tasks));
}

/** create program state initial pointer array  */
const program_init_func_t programInits[] = {
    title_program_init,
    game_program_init,
    result_program_init
};
/** create program state task pointer array  */
const program_func_t programs[] = {
    title_program,
    game_program,
    result_program,
};

/** main program
    @param data not used in this function  */
void program_control_main(__unused__ void* data){

    while(1){
        (programInits[ProgramState])();
        (programs[ProgramState])(data);
    }
}
