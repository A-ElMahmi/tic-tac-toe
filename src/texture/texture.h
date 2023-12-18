#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>


typedef struct Texture {
    SDL_Texture *texture;
    unsigned int width;
    unsigned int height;
} Texture;

typedef struct TextureRenderArgs {
    int x;
    int y;
    double angle;
    SDL_Point *center;
    SDL_RendererFlip flip;
    SDL_Rect *clip;
} TextureRenderArgs;

void texture_renderer_init(SDL_Renderer *renderer_);
void texture_create(Texture *self);
void texture_destroy(Texture *self);
bool texture_load_from_file(Texture *self, const char path[]);
bool texture_load_from_text(Texture *self, const char text[], TTF_Font *font, const SDL_Color text_color, const unsigned int wrap_length);
void texture_color_set(Texture *self, const Uint8 r, const Uint8 g, const Uint8 b);
void texture_blend_mode_set(Texture *self, const SDL_BlendMode blending);
void texture_alpha_set(Texture *self, const Uint8 alpha);
void texture_render(Texture *self, TextureRenderArgs args);


#endif