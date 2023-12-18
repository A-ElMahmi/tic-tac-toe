#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SDL.h>
#include <stdbool.h>


bool game_screen_media_load(void);
void game_screen_media_unload(void);
void game_screen_display(void);
void game_screen_event(SDL_Event *e);
void game_screen_update(void);


#endif