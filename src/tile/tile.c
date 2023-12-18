#include <stdbool.h>

#include "tile.h"
#include "..\globals.h"
#include "..\texture\texture.h"

void tile_create(Tile *self, int x, int y)
{
    self->x = x;
    self->y = y;
    self->width = 110;
    self->height = 110;
    self->player = NO_PLAYER;
    self->state = TILE_NO_STATE;
}

void tile_display(Tile *self)
{
    if (self->player != NO_PLAYER || self->state == TILE_ACTIVE_STATE)
    {
        texture_alpha_set(self->texture, 255);
        texture_render(self->texture, (TextureRenderArgs){self->x, self->y});
    }
    else
    {
        if (self->state == TILE_HOVER_STATE)
        {
            texture_alpha_set(self->texture, 40);
            texture_render(self->texture, (TextureRenderArgs){self->x, self->y});
        }
    }
}

bool tile_point_intersection(Tile *self, int x, int y)
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