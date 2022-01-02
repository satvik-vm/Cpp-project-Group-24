#pragma once

#include "Game.hpp"

class TextureManager    //Used to load the images of the objects
{
    public:
        static SDL_Texture* LoadTexture(const char* fileName);

};