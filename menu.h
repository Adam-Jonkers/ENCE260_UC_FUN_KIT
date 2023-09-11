// File:   menu.h 
// Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
// Date:   19 OCT 2022
// Descr:  Header file for menu.c

#ifndef MENU_H
#define MENU_H

/* Check if recived ready char and send ready char if start is pressed */
void CheckForPlayerReady (uint8_t *PlayersReady, const uint8_t Player, const uint8_t Opponent);

/* Display result from game  */
void DisplayEnd(char* state, char* displaytext, uint8_t winner, const uint8_t Player);

/* Display MainMenu */
void MainMenu(char* state, char* displaytext, uint8_t* PlayerReady, const uint8_t Player, const uint8_t Opponent);

/* Display Waiting for other player */
void Waiting(char* state, char* displaytext, uint8_t* PlayerReady, const uint8_t Player, const uint8_t Opponent);


#endif
