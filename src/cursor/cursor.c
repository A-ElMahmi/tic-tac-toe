#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "cursor.h"
#include "..\globals.h"
#include "..\texture\texture.h"


// SDL_Surface *cursor_default_surface;
// SDL_Surface *cursor_pointer_surface;

SDL_Cursor *cursor_default;
SDL_Cursor *cursor_pointer;


bool cursor_init()
{
    // cursor_default_surface = IMG_Load("assets\\cursor_default.png");
    // cursor_pointer_surface = IMG_Load("assets\\cursor_pointer.png");

    // if (cursor_default_surface == NULL || cursor_pointer_surface == NULL)
    // {
    //     return false;
    // }

    // cursor_default = SDL_CreateColorCursor(cursor_default_surface, 0, 0);
    // cursor_pointer = SDL_CreateColorCursor(cursor_pointer_surface, 5, 0);

    cursor_default = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursor_pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    return true;
}

void cursor_uninit()
{
    SDL_FreeCursor(cursor_default);
    SDL_FreeCursor(cursor_pointer);

    // SDL_FreeSurface(cursor_default_surface);
    // SDL_FreeSurface(cursor_pointer_surface);
}

void cursor_display()
{
    switch (cursor_type)
    {
        case CURSOR_DEFAULT:
            SDL_SetCursor(cursor_default);
            break;
        
        case CURSOR_POINTER:
            SDL_SetCursor(cursor_pointer);
            break;
    }
}