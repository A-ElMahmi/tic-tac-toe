#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#include "texture.h"


static SDL_Renderer *renderer = NULL;

void texture_renderer_init(SDL_Renderer *renderer_)
{
    renderer = renderer_;
}

void texture_create(Texture *self)
{
    self->texture = NULL;
    self->width = 0;
    self->height = 0;
}

void texture_destroy(Texture *self)
{
    if (self->texture != NULL)
    {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->width = 0;
        self->height = 0;
    }
}

bool texture_load_from_file(Texture *self, const char path[])
{
    texture_destroy(self);

    SDL_Texture *new_texture = NULL;

    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 255, 255));
    
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (new_texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else
        {
            self->width = loaded_surface->w;
            self->height = loaded_surface->h;
        }
        
        SDL_FreeSurface(loaded_surface);
    }

    self->texture = new_texture;

    return self->texture != NULL;
}

bool texture_load_from_text(Texture *self, const char text[], TTF_Font *font, const SDL_Color text_color, const unsigned int wrap_length)
{
    texture_destroy(self);

    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(font, text, text_color, wrap_length);
    if (text_surface == NULL)
    {
        printf("Unable to load text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        self->texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (self->texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            self->width = text_surface->w;
            self->height = text_surface->h;
        }

        SDL_FreeSurface(text_surface);
    }

    return self->texture != NULL;
}

void texture_color_set(Texture *self, const Uint8 r, const Uint8 g, const Uint8 b)
{
    SDL_SetTextureColorMod(self->texture, r, g, b);
}

void texture_blend_mode_set(Texture *self, const SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(self->texture, blending);
}

void texture_alpha_set(Texture *self, const Uint8 alpha)
{
    SDL_SetTextureAlphaMod(self->texture, alpha);
}

void texture_render(Texture *self, TextureRenderArgs args)
{
    // Set defaults
    if (args.clip == 0)
    {
        args.clip = NULL;
    }
    if (args.center == 0)
    {
        args.center = NULL;
    }
    if (args.flip == 0)
    {
        args.flip = SDL_FLIP_NONE;
    }

    SDL_Rect render_quad = {args.x, args.y, self->width, self->height};

    if (args.clip != NULL)
    {
        render_quad.w = args.clip->w;
        render_quad.h = args.clip->h;
    }

    SDL_RenderCopyEx(renderer, self->texture, args.clip, &render_quad, args.angle, args.center, args.flip);
}
