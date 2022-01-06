#pragma once

#include "Game.hpp"
#include<string.h>

class Tile
{
    public:
        Tile(const char*, int, int, int);
        ~Tile();
        int getX();
        int getY();
        int getWidth();
        void Update(int);
        void Render();
        SDL_Rect getRect();
        // int val = 1;

    private:
        int xpos;
        int ypos; 
        int width;
        // int speed;
        SDL_Texture* objTexture;
        SDL_Rect srect, drect;
};