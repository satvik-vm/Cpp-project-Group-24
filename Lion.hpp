#pragma once

#include "Game.hpp"
#include<string.h>

class Lion
{
    public:
        Lion(const char*);
        ~Lion();
        void Update(int);
        void Render();
        SDL_Rect getRect();
        int getX();
        void setPos(int);

    private:
        SDL_Texture* objTexture;
        SDL_Rect srect; 
        SDL_Rect drect;
        int lionSpeed = 4;
        int basePos = 1000;
};