#include <stdbool.h>

#include "button.h"
#include "..\globals.h"
#include "..\texture\texture.h"


static bool button_point_intersection(Button *self, int x, int y)
{
    if (x > self->x && x < self->x + self->width)
    {
        if (y > self->y && y < self->y + self->height)
        {
            return true;
        }
    }
    return false;
}

void button_create(Button *self, Texture *texture, int x, int y)
{
    self->texture = texture;
    self->x = x;
    self->y = y;
    self->width = self->texture->width;
    self->height = self->texture->height;
    self->texture_x = self->x;
    self->texture_y = self->y;
    self->state = BUTTON_NO_STATE;
}

void button_display(Button *self)
{
    texture_render(self->texture, (TextureRenderArgs){self->texture_x, self->texture_y});
}

bool button_event_handle(Button *self, SDL_Event *e)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (button_point_intersection(self, mouse_x, mouse_y))
    {
        switch (e->type)
        {
            case SDL_MOUSEMOTION:
                cursor_type = CURSOR_POINTER;
                self->state = BUTTON_HOVER_STATE;
                break;

            case SDL_MOUSEBUTTONDOWN:
                cursor_type = CURSOR_POINTER;
                if (e->button.button == SDL_BUTTON_LEFT)
                {
                    self->state = BUTTON_ACTIVE_STATE;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (e->button.button == SDL_BUTTON_LEFT)
                {
                    self->state = BUTTON_NO_STATE;
                    return true;
                }
        }
    }
    else
    {
        self->state = BUTTON_NO_STATE;
    }
    
    return false;
}

void button_update(Button *self)
{
    switch (self->state)
    {
        case BUTTON_NO_STATE:
            texture_alpha_set(self->texture, 255);
            self->texture->width = self->width;
            self->texture->height = self->height;
            break;

        case BUTTON_HOVER_STATE:
            texture_alpha_set(self->texture, 190);
            break;

        case BUTTON_ACTIVE_STATE:
            self->texture->width = self->width - 2;
            self->texture->height = self->height - 2;
            self->texture_x = self->x + 1;
            self->texture_y = self->y + 1;
            break;
    }
}
