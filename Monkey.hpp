#pragma once

#include "Game.hpp"
#include "TextureManager.h"

class Monkey
{
    public:
        Monkey(const char*, int, int, int);
        ~Monkey();
        void Update(int);
        void Render();
        int getX();
        int getY();
        int getHeight();
        SDL_Rect getRect(); //Returns the destination rectangle(drect) of the Monkey to check for collisions 
        void setPos(int pos);   //Resets the position

    private:
        int xpos;
        int ypos;
        int height;
        int monkeySpeed;
        double angle;
        SDL_Texture* objTexture;
        SDL_Rect srect, drect;
        SDL_Point hingePoint;   //The point about which the monkey rotates
};