#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "..\texture\texture.h"

typedef enum {
    BUTTON_NO_STATE,
    BUTTON_HOVER_STATE,
    BUTTON_ACTIVE_STATE
} ButtonState;

typedef struct Button {
    Texture *texture;
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    int texture_x;
    int texture_y;
    ButtonState state;
} Button;

void button_create(Button *self, Texture *texture_, int x, int y);
void button_display(Button *self);
bool button_event_handle(Button *self, SDL_Event *e);
void button_update(Button *self);

#endif