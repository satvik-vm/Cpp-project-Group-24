#pragma once

#include "Game.hpp"

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char*);   //For loading images
        static SDL_Texture* LoadText(TTF_Font*, const char*, SDL_Color);    //For loading texts
};