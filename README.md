```
University of Canterbury
ENCE260 Assignment
19th October 2022
Liam Morrison (lmo99), Adam Jonkers (ajo164)

```

# UC FUN KIT: Group_333

The objective of the game is to activate the most lights. A light is activated by moving the joystick in the corrosponding direction eg. down turns on the light at the bottom of the screen. This will also deactivate your opponents light. The winner is the player the most lights activated at the end of the game. By defult games will last 10 seconds. To begin the game both players must push in the joystick. 

## Installation

To install move files to the `ence260-ucfk4/assignment/final` folder.

## Settings

There are two configurable settings these can both be changed by editing the #define at the begining of game.c. 

The first setting GAME_LENGTH can be editied by changing the value (defult 10) to a value in seconds this will set the length of the game.

The second setting GAME_BOARD (defult true) toggles the optional game board. if the game board is disabled the only display during the game will be the activated lights.


