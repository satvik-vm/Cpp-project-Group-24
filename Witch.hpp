#pragma once

#include "Game.hpp"
#include "TextureManager.h"

class Witch
{
    public:
        Witch(const char*, int, int, int, int);
        ~Witch();
        void Update(int speed);
        void Render();
        SDL_Rect getRect(); //Returns the destination rectangle(drect) of the witch to check for collisions 

    private:
        int xpos;
        int ypos;
        int tileXPos;
        int tileYPos;
        int tileWidth;
        int buffer = 20;
        int val;        //val > 0 -> witch    val < 0 -> witch is flipped
        int minPos;
        string state;
        SDL_Texture* objTexture;
        SDL_Rect srect; 
        SDL_Rect drect;
};