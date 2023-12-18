#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SDL.h>
#include <stdbool.h>

#include "globals.h"


bool menu_screen_media_load();
void menu_screen_media_unload();
State menu_screen_update(SDL_Event *e);
void menu_screen_display();


#endif