#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#include "game_screen.h"
#include "globals.h"
#include "tile\tile.h"
#include "texture\texture.h"


Texture background_texture;
Texture board_texture;
Texture x_texture;
Texture o_texture;

Tile tiles[3][3];

static void bot_run(void);
static int minimax(Players board_[3][3], bool maximising_player);


static void tiles_update_texture(void)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == PLAYER_X)
            {
                tiles[row][col].player = PLAYER_X;
                tiles[row][col].texture = &x_texture;
            }
            else if (board[row][col] == PLAYER_O)
            {
                tiles[row][col].player = PLAYER_O;
                tiles[row][col].texture = &o_texture;
            }
            else if (board[row][col] == NO_PLAYER)
            {
                tiles[row][col].texture = current_player == PLAYER_X ? &x_texture : &o_texture;
            }
        }
    }
}

static bool check_winner(Players board_[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if ((board_[row][0] == board_[row][1] && board_[row][1] == board_[row][2]) && board_[row][0] != NO_PLAYER)
        {
            return true;
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if ((board_[0][col] == board_[1][col] && board_[1][col] == board_[2][col]) && board_[0][col] != NO_PLAYER)
        {
            return true;
        }
    }

    if ((board_[0][0] == board_[1][1] && board_[1][1] == board_[2][2]) && board_[0][0] != NO_PLAYER)
    {
        return true;
    }

    if ((board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0]) && board_[0][2] != NO_PLAYER)
    {
        return true;
    }

    return false;
}

static bool check_draw(Players board_[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board_[row][col] == NO_PLAYER)
            {
                return false;
            }
        }
    }

    return true;
}

static void copy_board(Players destination[3][3], Players source[3][3]){
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            destination[row][col] = source[row][col];
        }
    }
}

bool game_screen_media_load(void)
{
    texture_create(&background_texture);
    texture_create(&board_texture);
    texture_create(&x_texture);

    if (!texture_load_from_file(&background_texture, "assets\\board_bg.png") || 
        !texture_load_from_file(&board_texture, "assets\\board_grid.png") ||
        !texture_load_from_file(&o_texture, "assets\\o_shape.png") ||
        !texture_load_from_file(&x_texture, "assets\\x_shape.png"))
    {
        return false;
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            tile_create(&tiles[row][col], 145 + (col * 120), 65 + (row * 120));
        }
    }

    return true;
}

void game_screen_media_unload(void)
{
    texture_destroy(&background_texture);
    texture_destroy(&board_texture);
    texture_destroy(&x_texture);
    texture_destroy(&o_texture);
}

void game_screen_display(void)
{
    texture_render(&background_texture, (TextureRenderArgs){0, 0});
    texture_render(&board_texture, (TextureRenderArgs){145, 65});

    tiles_update_texture();
    
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            tile_display(&tiles[row][col]);
        }
    }
}

void game_screen_event(SDL_Event *e)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (tiles[row][col].player == NO_PLAYER)
            {
                if (tile_point_intersection(&tiles[row][col], mouse_x, mouse_y))
                {
                    switch (e->type)
                    {
                        case SDL_MOUSEMOTION:
                            cursor_type = CURSOR_POINTER;
                            tiles[row][col].state = TILE_HOVER_STATE;
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            cursor_type = CURSOR_POINTER;
                            if (e->button.button == SDL_BUTTON_LEFT)
                            {
                                tiles[row][col].state = TILE_ACTIVE_STATE;
                                board[row][col] = current_player;

                                current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
                            }
                            break;
                    }
                }
                else
                {
                    tiles[row][col].state = TILE_NO_STATE;
                }
            }
        }
    }
}

void game_screen_update(void)
{
    if (bot_playing && current_player == PLAYER_O && !check_winner(board) && !check_draw(board))
    {
        bot_run();
    }

    if (check_winner(board))
    {
        Players previous_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X; 
        winner_player = previous_player;
        return;
    }

    if (check_draw(board))
    {
        winner_player = DRAW;
        return;
    }
}

static void bot_run(void)
{
    int max_eval = INT_MIN;
    unsigned int move_x;
    unsigned int move_y;
    Players board_[3][3];
    copy_board(board_, board);


    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board_[row][col] == NO_PLAYER)
            {
                board_[row][col] = PLAYER_O;
                int eval = minimax(board_, false);
                board_[row][col] = NO_PLAYER;

                if (eval > max_eval)
                {
                    max_eval = eval;
                    move_x = row;
                    move_y = col; 
                }
            }
        }
    }

    board[move_x][move_y] = PLAYER_O;
    current_player = PLAYER_X;
}

static int minimax(Players board_[3][3], bool maximising_player)
{
    if (check_winner(board_))
    {
        return maximising_player ? -1 : 1;
    }
    else if (check_draw(board_))
    {
        return 0;
    }

    if (maximising_player)
    {
        int max_eval = INT_MIN;

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board_[row][col] == NO_PLAYER)
                {
                    board_[row][col] = PLAYER_O;
                    int eval = minimax(board_, false);
                    board_[row][col] = NO_PLAYER;
                    max_eval = fmax(max_eval, eval);
                }
            }
        }

        return max_eval;
    }
    else
    {
        int min_eval = INT_MAX;

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board_[row][col] == NO_PLAYER)
                {
                    board_[row][col] = PLAYER_X;
                    int eval = minimax(board_, true);
                    board_[row][col] = NO_PLAYER;
                    min_eval = fmin(min_eval, eval);
                }
            }
        }

        return min_eval;
    }
}