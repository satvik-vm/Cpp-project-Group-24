#pragma once

#include "Game.hpp"
#include "TextureManager.h"

class Tile
{
    public:
        Tile(const char*, int, int, int);
        ~Tile();
        int getX(); //Returns the X position of the tile
        int getY(); //Returns the Y position of the tile
        int getWidth(); //Returns the width of the tile
        void Update(int);
        void Render();
        SDL_Rect getRect(); //Returns the destination rectangle (drect) of the tile to check for collisions

    private:
        int xpos;
        int ypos; 
        int width;
        SDL_Texture* objTexture;
        SDL_Rect srect, drect;
};