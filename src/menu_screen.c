#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "menu_screen.h"
#include "globals.h"
#include "texture\texture.h"
#include "button\button.h"


Texture background_texture;
Texture title_texture;

Texture singleplayer_texture;
Button singleplayer_button;
Texture multiplayer_texture;
Button multiplayer_button;

bool menu_screen_media_load()
{
    texture_create(&background_texture);
    texture_create(&title_texture);

    texture_create(&singleplayer_texture);
    texture_create(&multiplayer_texture);
    
    if (!texture_load_from_file(&background_texture, "assets\\menu_bg.png") || 
        !texture_load_from_file(&title_texture, "assets\\menu_title.png") ||
        !texture_load_from_file(&singleplayer_texture, "assets\\singleplayer_btn.png") ||
        !texture_load_from_file(&multiplayer_texture, "assets\\multiplayer_btn.png"))
    {
        return false;
    }

    button_create(&singleplayer_button, &singleplayer_texture, 60, 300);
    button_create(&multiplayer_button, &multiplayer_texture, 340, 300);

    return true;
};

void menu_screen_media_unload()
{
    texture_destroy(&background_texture);
    texture_destroy(&title_texture);
    texture_destroy(&singleplayer_texture);
    texture_destroy(&multiplayer_texture);
}

State menu_screen_update(SDL_Event *e)
{
    if (button_event_handle(&singleplayer_button, e))
    {
        bot_playing = true;
        return GAME_STATE;
    }
    
    if (button_event_handle(&multiplayer_button, e))
    {
        bot_playing = false;
        return GAME_STATE;
    }

    button_update(&singleplayer_button);
    button_update(&multiplayer_button);

    return MENU_STATE;
}

void menu_screen_display()
{
    texture_render(&background_texture, (TextureRenderArgs){0, 0});
    texture_render(&title_texture, (TextureRenderArgs){0, 100});

    button_display(&singleplayer_button);
    button_display(&multiplayer_button);
}