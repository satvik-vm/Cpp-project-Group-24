#pragma once

#include "Game.hpp"
#include<string.h>

class MysteryBox
{
    public:
        MysteryBox(const char*, int, int, int);
        ~MysteryBox();
        void Update(int);
        void Render();
        int isTouched();
        int getX();
        int getY();
        SDL_Rect getRect();

    private:
        int xpos;
        int ypos;
        SDL_Texture* objTexture;
        SDL_Rect srect;
        SDL_Rect drect;
        int val = 1;
        int type;
};