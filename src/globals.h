#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>


typedef enum {
    MENU_STATE,
    GAME_STATE,
    WIN_STATE
} State;

typedef enum {
    NO_PLAYER,
    PLAYER_X,
    PLAYER_O,
    DRAW
} Players;

typedef enum {
    CURSOR_DEFAULT,
    CURSOR_POINTER
} CursorType;

const extern unsigned int SCREEN_WIDTH;
const extern unsigned int SCREEN_HEIGHT;

extern Players current_player;
extern Players winner_player;
bool bot_playing;

extern Players board[3][3];

CursorType cursor_type;


#endif