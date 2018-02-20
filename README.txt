PONG!
author: Wen Yu

How to play:
1. Turn on both devices.
2. One player push the navswitch push button to start the game, the other 
   device will start automatically. The player who pushes the button first will 
   first serve.
3. Use navswitch to control the paddle left, right, up and down.
4. When one player lose, 'LOSE' is shown in the screen and 'WIN' is shown in 
   the opponent's screen. The led on winner's board will flash.
5. After a couple of seconds, the game return to title page. Now you can start
   a game again.

Structure of the program:

The program is running on three stages:
1. Title stage
2. Game stage
3. Result stage

Each stage uses task loop to run and can be terminated by changing the 
ProgrameState flag defined in program_control.c
It is possible to add multiple games into this program by add new game file into
game folder and only modify program_control.c file.


In program folder:
program_control: control three program stages 
title: define all tasks for title stage
result: define all tasks for result stage

In game folder:
pong: the pong
