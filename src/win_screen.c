#include <SDL.h>

#include "win_screen.h"
#include "globals.h"
#include "texture\texture.h"
#include "button\button.h"


Texture background_texture;
Texture x_win_texture;
Texture o_win_texture;
Texture draw_texture;

Texture *title_text;

Texture play_again_texture;
Button play_again_button;
Texture main_menu_texture;
Button main_menu_button;


bool win_screen_media_load()
{
    texture_create(&background_texture);
    texture_create(&play_again_texture);
    texture_create(&main_menu_texture);

    if (!texture_load_from_file(&background_texture, "assets\\menu_bg.png") ||
        !texture_load_from_file(&play_again_texture, "assets\\play_again_btn.png") ||
        !texture_load_from_file(&main_menu_texture, "assets\\main_menu_btn.png"))
    {
        return false;
    }

    button_create(&play_again_button, &play_again_texture, 60, 300);
    button_create(&main_menu_button, &main_menu_texture, 340, 300);

    switch (winner_player)
    {
        case PLAYER_X:
            texture_create(&x_win_texture);
            if (!texture_load_from_file(&x_win_texture, "assets\\x_won.png"))
            {
                return false;
            }
            title_text = &x_win_texture;
            break;

        case PLAYER_O:
            texture_create(&o_win_texture);
            if (!texture_load_from_file(&o_win_texture, "assets\\o_won.png"))
            {
                return false;
            }
            title_text = &o_win_texture;
            break;

        case DRAW:
            texture_create(&draw_texture);
            if (!texture_load_from_file(&draw_texture, "assets\\draw.png"))
            {
                return false;
            }
            title_text = &draw_texture;
            break;
    }

    return true;
}

void win_screen_media_unload()
{
    texture_destroy(&background_texture);
    texture_destroy(&play_again_texture);
    texture_destroy(&main_menu_texture);
    texture_destroy(&x_win_texture);
    texture_destroy(&o_win_texture);
    texture_destroy(&draw_texture);
}

State win_screen_update(SDL_Event *e)
{
    if (button_event_handle(&main_menu_button, e))
    {
        return MENU_STATE;
    }

    if (button_event_handle(&play_again_button, e))
    {
        return GAME_STATE;
    }

    button_update(&main_menu_button);
    button_update(&play_again_button);

    return WIN_STATE;
}

void win_screen_display()
{
    texture_render(&background_texture, (TextureRenderArgs){0, 0});
    texture_render(title_text, (TextureRenderArgs){145, 90});

    button_display(&play_again_button);
    button_display(&main_menu_button);
}
