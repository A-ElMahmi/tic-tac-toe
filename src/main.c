#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "menu_screen.h"
#include "game_screen.h"
#include "win_screen.h"
#include "globals.h"
#include "texture\texture.h"
#include "cursor\cursor.h"


bool game_init();
void game_close();
void game_reset();
void change_current_state(State new_state);

SDL_Window  *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

State g_current_state;


int main(int argc, char* argv[])
{
    bool game_running = true;
    SDL_Event e;


    if (!game_init() || !cursor_init())
    {
        game_close();
    }

    change_current_state(MENU_STATE);

    while (game_running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            cursor_type = CURSOR_DEFAULT;

            if (e.type == SDL_QUIT)
            {
                game_running = false;
            }

            switch (g_current_state)
            {
                case MENU_STATE:
                    if (menu_screen_update(&e) == GAME_STATE)
                    {
                        change_current_state(GAME_STATE);
                    }
                    break;

                case GAME_STATE:
                    game_screen_event(&e);
                    break;

                case WIN_STATE:
                    if (win_screen_update(&e) == MENU_STATE)
                    {
                        change_current_state(MENU_STATE);
                    }
                    else if (win_screen_update(&e) == GAME_STATE)
                    {
                        change_current_state(GAME_STATE);
                    }
                    break;
            }

            if ((winner_player != NO_PLAYER || winner_player == DRAW) && g_current_state != WIN_STATE)
            {
                change_current_state(WIN_STATE);
                game_reset();
            }
        }

        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
        SDL_RenderClear(g_renderer);

        if (g_current_state == MENU_STATE)
        {
            menu_screen_display();
        }
        else if (g_current_state == GAME_STATE)
        {
            game_screen_display();
            game_screen_update();
        }
        else if (g_current_state == WIN_STATE)
        {
            win_screen_display();
        }
        
        cursor_display();

        SDL_RenderPresent(g_renderer);
    }

    game_close();

    return 0;
}

bool game_init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create Window
    g_window = SDL_CreateWindow(
        "Tic Tac Toe", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (g_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create Renderer
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_Image
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        printf("SDL_image failed to initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        printf("SDL_ttf failed to initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    // Initialize texture_renderer
    texture_renderer_init(g_renderer);

    // Window Icon
    SDL_Surface *icon_surface = IMG_Load("assets\\icon.png");
    SDL_SetWindowIcon(g_window, icon_surface);
    // SDL_FreeSurface(icon_surface);

    return true;
}

void game_close()
{
    menu_screen_media_unload();
    game_screen_media_unload();
    cursor_uninit();

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void game_reset()
{
    current_player = PLAYER_X;
    winner_player = NO_PLAYER;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = NO_PLAYER;
        }
    }
}

void change_current_state(State new_state)
{
    switch (new_state)
    {
        case MENU_STATE:
            game_screen_media_unload();
            win_screen_media_unload();

            menu_screen_media_load();
            g_current_state = MENU_STATE;
            break;
            
        case GAME_STATE:
            menu_screen_media_unload();
            win_screen_media_unload();

            game_screen_media_load();
            g_current_state = GAME_STATE;
            break;

        case WIN_STATE:
            menu_screen_media_unload();
            game_screen_media_unload();

            win_screen_media_load();
            g_current_state = WIN_STATE;
            break;
    }
}