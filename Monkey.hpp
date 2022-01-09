#pragma once

#include "Game.hpp"
#include<string.h>

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
        SDL_Rect getRect();
        void setPos(int pos);

    private:
        int xpos;
        int ypos;
        int height;
        SDL_Texture* objTexture;
        SDL_Rect srect;
        SDL_Rect drect;
        double angle = -100.0;
        SDL_Point hingePoint;
};