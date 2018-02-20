/**  @file   game.c
     @author Wen yu wyu18 
             Jaimie Ralfe jtr39
     @brief  main file
*/

#include "system.h"
#include "program_control.h"

int main (void)
{
    system_init();
    program_control_main(0);

    return 0;
}
