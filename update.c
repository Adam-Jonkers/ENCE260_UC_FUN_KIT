// File:   update.c 
// Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
// Date:   19 OCT 2022
// Descr:  Update control c file for game */

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

void PixelUpdate(uint8_t PixelNumber, uint8_t state)
{
    /* updating the pixel depending on state and which pixel need changing*/
    switch (PixelNumber)
    {
    case 0:
    /* RIGHT */
        tinygl_pixel_set(tinygl_point(2,0), state);
        break;
    case 1:
    /* LEFT */
        tinygl_pixel_set(tinygl_point(2,6), state);
        break;
    case 2:
    /* UP */
        tinygl_pixel_set(tinygl_point(4,3), state);
        break;
    case 3:
    /* DOWN */
        tinygl_pixel_set(tinygl_point(0,3), state);
        break;
    case 4:
    /* PUSH */
        tinygl_pixel_set(tinygl_point(2,3), state);
        break;
    }
}

void GetOponentInput(uint8_t* buttons, const uint8_t Opponent) {
    /* adding oppnenet input to players 'buttons' list*/
    char Input;
    Input = ir_uart_getc();
    switch (Input)
    {
    case '0':
        buttons[0] = Opponent;
        break;
    case '1':
        buttons[1] = Opponent;
        break;
    case '2':
        buttons[2] = Opponent;
        break;
    case '3':
        buttons[3] = Opponent;
        break;
    case '4':
        buttons[4] = Opponent;
        break;            
    default:
        break;
    }
}

void UpdateLedMatrix(uint8_t* buttons, const uint8_t Player) {
    /* calls updates of pixels depnding on their state in buttons */
    for (uint8_t i = 0; i < 5; i++) {
        if (buttons[i] == Player) {
            PixelUpdate(i, 1);
        } else {
            /* turn off pixel*/
            PixelUpdate(i, 0);
        }
    }
    tinygl_update ();
}
