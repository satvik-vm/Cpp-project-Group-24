#pragma once

#include "Game.hpp"
#include "TextureManager.h"

class Lion
{
    public:
        Lion(const char*);
        ~Lion();
        void Update(int);
        void Render();
        SDL_Rect getRect();  //Returns the destination rectangle(drect) of the Lion to check for collisions 
        int getX();
        void setPos(int);   //Resets the position of the lion

    private:
        int lionSpeed;
        int basePos;
        SDL_Texture* objTexture;
        SDL_Rect srect; 
        SDL_Rect drect;
};