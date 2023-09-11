// File:   game.c
// Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
// Date:   19 OCT 2022
// Descr:  main file C file for game */

#include <stdint.h>
#include <string.h>

#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "timer.h"
#include "ir_uart.h"
#include "menu.h"
#include "update.h"


#define GAME_LENGTH 10 // Set length of game in seconds
#define GAME_BOARD true // toggle game board

#define PLAYER 0 // Set player
#define OPPONENT 1 // Set opponent
#define DRAW_NUMBER 2 // Set draw check value
#define PACER_RATE 500 // Set speed of game refresh
#define MESSAGE_RATE 10 // Set scrolling rate of text
#define TIMER_CONST 255
#define BUTTONS_SIZE 5



void GameSetup(char* state, uint8_t* buttons, uint8_t* Roughtimer1, uint8_t* Roughtimer2) {
    /* sets up game after both players are ready */
    for(uint8_t i = 0 ; i < BUTTONS_SIZE ; i++) { // setting all of buttons to a nuetral number 
        buttons[i] = DRAW_NUMBER;
    }
    tinygl_clear();
    
    if (GAME_BOARD) {
        tinygl_pixel_set(tinygl_point(1,0), 1);
        tinygl_pixel_set(tinygl_point(3,0), 1);
        tinygl_pixel_set(tinygl_point(2,1), 1);
        tinygl_pixel_set(tinygl_point(0,2), 1);
        tinygl_pixel_set(tinygl_point(2,2), 1);
        tinygl_pixel_set(tinygl_point(4,2), 1);
        tinygl_pixel_set(tinygl_point(1,3), 1);
        tinygl_pixel_set(tinygl_point(3,3), 1);
        tinygl_pixel_set(tinygl_point(0,4), 1);
        tinygl_pixel_set(tinygl_point(2,4), 1);
        tinygl_pixel_set(tinygl_point(4,4), 1);
        tinygl_pixel_set(tinygl_point(2,5), 1);
        tinygl_pixel_set(tinygl_point(1,6), 1);
        tinygl_pixel_set(tinygl_point(3,6), 1);
    }
    *Roughtimer1 = 0;
    *Roughtimer2 = 0;
    *state = 'P';
}

uint8_t GameWrapUp(uint8_t* buttons) {
    /* Count scores to find winner */
    uint8_t winner = DRAW_NUMBER; /* winner displayed by value of this varible if 2 is a draw */
    uint8_t PlayerScore = 0;
    uint8_t OpponentScore = 0;
    for (uint8_t i = 0; i < BUTTONS_SIZE; i++) {
        if (buttons[i] == PLAYER) {
            PlayerScore ++;
        } else if (buttons[i] == OPPONENT) {
            OpponentScore ++;
        }
    }
    if (PlayerScore > OpponentScore) { // determines from scores who is winner or is it is a draw
        winner = PLAYER;
    } else if (OpponentScore > PlayerScore) {
        winner = OPPONENT;
    }
    return winner;
}

void PlayGame(char* state, uint8_t* buttons, uint8_t* winner, uint8_t* Roughtimer1, uint8_t* Roughtimer2) {
    /*carries out main gameplay by checking inputs */
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) { 
        buttons[0] = PLAYER;
        ir_uart_putc('0');
    } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        buttons[1] = PLAYER;
        ir_uart_putc('1');
    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        buttons[2] = PLAYER;
        ir_uart_putc('2');
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        buttons[3] = PLAYER;
        ir_uart_putc('3');
    } else if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        buttons[4] = PLAYER;
        ir_uart_putc('4');
    }
    /*checking for oppnent inputs*/
    if (ir_uart_read_ready_p()) {
        GetOponentInput(buttons, OPPONENT);
    }
    UpdateLedMatrix(buttons, PLAYER);
    *Roughtimer1 += 1;
    if (*Roughtimer1 >= TIMER_CONST) {
        *Roughtimer1 = 0;
        *Roughtimer2 +=1;
    }

    if (*Roughtimer2 >= ((PACER_RATE * GAME_LENGTH)/TIMER_CONST)) {
        *winner = GameWrapUp(buttons);
        *state = 'E';
    }
}

int main (void)
{
    /*  Game states
        M = Main Menu
        W = Wating
        S = Game Setup
        P = Play Game
        E = End Display
    */

    char state = 'M';
    char displaytext[20] = "";

    system_init ();
    navswitch_init();
    ir_uart_init();

    tinygl_text(displaytext);

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    pacer_init (PACER_RATE);

    uint8_t buttons[5];
    /*  Button Values
        0 = Right
        1 = Left
        2 = Up
        3 = Down
        4 = Push
    */
    uint8_t winner = DRAW_NUMBER;
    uint8_t PlayersReady[2] = {0, 0};
    uint8_t Roughtimer1;
    uint8_t Roughtimer2;

    while (1) {
        pacer_wait();
        navswitch_update();
        switch(state) {
        case 'M':
            MainMenu(&state, displaytext, PlayersReady, PLAYER, OPPONENT);
            break;
        case 'W':
            Waiting(&state, displaytext, PlayersReady, PLAYER, OPPONENT);
            break;
        case 'S':
            GameSetup(&state, buttons, &Roughtimer1, &Roughtimer2);
            break;
        case 'P':
            PlayGame(&state, buttons, &winner, &Roughtimer1, &Roughtimer2);
            break;        
        case 'E':
            DisplayEnd(&state, displaytext, winner, PLAYER);
            break;
        }
    }
}




