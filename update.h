/*File:   update.h 
Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
Date:   19 OCT 2022
Descr:  Header file for update.c */

#ifndef UPDATE_H
#define UPDATE_H

/* Set pixel to state */
void PixelUpdate(uint8_t PixelNumber, uint8_t state);

/* Recieve Input from opponent and update array */
void GetOponentInput(uint8_t* buttons, const uint8_t Opponent);

/* Set States of pixels from array */
void UpdateLedMatrix(uint8_t* buttons, const uint8_t Player);


#endif
