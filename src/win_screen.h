#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <SDL.h>
#include <stdbool.h>

#include "globals.h"


bool win_screen_media_load();
void win_screen_media_unload();
State win_screen_update(SDL_Event *e);
void win_screen_display();


#endif