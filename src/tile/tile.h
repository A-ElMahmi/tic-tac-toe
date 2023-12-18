#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

#include "..\globals.h"
#include "..\texture\texture.h"


typedef enum {
    TILE_NO_STATE,
    TILE_HOVER_STATE,
    TILE_ACTIVE_STATE
} TileState;

typedef struct {
    Players player;
    Texture *texture;
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    TileState state;
} Tile;

void tile_create(Tile *self, int x, int y);
void tile_display(Tile *self);
bool tile_point_intersection(Tile *self, int x, int y);

#endif