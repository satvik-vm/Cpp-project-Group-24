#pragma once

#include "Game.hpp"
#include "TextureManager.h"

class MysteryBox
{
    public:
        MysteryBox(const char*, int, int, int);
        ~MysteryBox();
        void Update(int);
        int isTouched();    //Returns 1 if the box is touched
        void Render();
        int getX(); //Returns X coordinate of the box 
        int getY(); //Returns Y coordinate of the box
        SDL_Rect getRect(); //Returns the destination rectangle(drect) of the box to check for collisions 

    private:
        int xpos;
        int ypos;
        int val = 1;
        int type;
        SDL_Texture* objTexture;
        SDL_Rect srect, drect;
};