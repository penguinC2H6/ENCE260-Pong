/**  @file   program_control.c
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  this module controls the whole program. it switches the program 
             in the three stage: title, game, result. This module is built based 
             on task.c
*/
#ifndef PROGRAM_CONTROL_H
#define PROGRAM_CONTROL_H

#include "system.h"
#include "timer.h"

#define TASK_RATE TIMER_RATE

/** program state type  */
typedef enum {
    TITLE,
    GAME,
    RESULT
} program_state_t;
/** player type  */
typedef enum {
    MASTER,
    SLAVE,
    EQUAL
} player_type_t;
/** game result type  */
typedef enum{
    WIN,
    LOSE,
    DRAW
} game_result_t;
/** score type  */
typedef struct score_s{
    uint8_t mine;
    uint8_t player;
} score_t;

/** Program state, Title, Game, Result  */
extern program_state_t ProgramState;
/** player type, master,slave or equal  */
extern player_type_t PlayerType;
/** final game result  */
extern game_result_t GameResult;
/** game score  */
extern score_t GameScore;

/** main program
    @param data not used in this function  */
void program_control_main(__unused__ void* data);

#endif
