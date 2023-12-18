#include "globals.h"

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

Players current_player = PLAYER_X;
Players winner_player = NO_PLAYER;

Players board[3][3] = {NO_PLAYER};

CursorType cursor_type = CURSOR_DEFAULT;