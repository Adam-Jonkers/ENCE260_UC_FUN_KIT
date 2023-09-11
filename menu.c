// File:   menu.c 
// Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
// Date:   19 OCT 2022
// Descr:  Menu control C file for game */

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

#define DRAW_NUMBER 2 // Set draw check value


void CheckForPlayerReady (uint8_t *PlayersReady, const uint8_t Player, const uint8_t Opponent)
{
    /* checks if a player is ready to play*/
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {

        PlayersReady[Player] = 1;
        ir_uart_putc('R');
    }
    if (ir_uart_read_ready_p()) {
        char ch;
        ch = ir_uart_getc();
        if (ch == 'R') {
            PlayersReady[Opponent] = 1;
        }
    }

}

void DisplayEnd(char* state, char* displaytext, uint8_t winner, const uint8_t Player) {
    /* disply end screen dpeending on the winner*/
    if (winner == Player) {
        if (strcmp(displaytext, "Winner") != 0) {
            strcpy (displaytext, "Winner");
            tinygl_text(displaytext);
        }
    } else if (winner == DRAW_NUMBER)
    {
        if (strcmp(displaytext, "Draw") != 0) {
            strcpy (displaytext, "Draw");
            tinygl_text(displaytext);
        }
    } else if (winner != Player) {
        if (strcmp(displaytext, "Loser") != 0) {
            strcpy (displaytext, "Loser");
            tinygl_text(displaytext);
        }
    }

    tinygl_update ();
    
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        *state = 'M';
    }
}

void MainMenu(char* state, char* displaytext, uint8_t* PlayerReady, const uint8_t Player, const uint8_t Opponent) {
    /* display main menu */
    if (strcmp(displaytext, "Push down to start") != 0) {
        strcpy (displaytext, "Push down to start");
        tinygl_text(displaytext);
    }
    
    tinygl_update ();

    CheckForPlayerReady(PlayerReady, Player, Opponent);
    if (PlayerReady[Player] == 1 ) {
        *state = 'W';
    }

}

void Waiting(char* state, char* displaytext, uint8_t* PlayerReady, const uint8_t Player, const uint8_t Opponent) {
    /* Display waiting for other player */
    if (strcmp(displaytext, "Waiting for player") != 0) {
        strcpy (displaytext, "Waiting for player");
        tinygl_text(displaytext);
    }
    tinygl_update();

    CheckForPlayerReady(PlayerReady, Player, Opponent);
    if (PlayerReady[0] == 1 && PlayerReady[1] == 1) {
        *state = 'S';
        PlayerReady[0] = 0;
        PlayerReady[1] = 0;

    }
}
