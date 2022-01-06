#pragma once

#include "Game.hpp"
#include<string.h>

class Witch
{
    public:
        Witch(const char*, int, int, int, int);
        ~Witch();
        void Update(int);
        void Render();
        int isTouched();
        SDL_Rect getRect();

    private:
        int xpos;
        int ypos;
        int minPos;
        int val;
        string state;
        int tileXPos;
        int tileYPos;
        int tileWidth;
        int buffer = 20;
        SDL_Texture* objTexture;
        SDL_Rect srect; 
        SDL_Rect drect;
};