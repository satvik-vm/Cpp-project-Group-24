#include "Tile.hpp"
#include "TextureManager.h"

Tile::Tile(const char* fileName, int x, int y, int w)
{
    objTexture = TextureManager::LoadTexture(fileName);//Loading the image

    //Setting the x position, y position and the width of the tile
    xpos = x;
    ypos = y;
    width = w;
    // speed = Game::speed;
}

Tile::~Tile() {}

void Tile::Update(int speed)
{
    xpos = xpos-speed;

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;

    drect.x = xpos;
    drect.y = ypos;
    drect.w = width;
    drect.h = 30;
}

void Tile::Render()
{
    SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_NONE);
}

int Tile::getX()
{
    return xpos;
}

int Tile::getY()
{
    return ypos;
}

int Tile::getWidth()
{
    return width;
}

SDL_Rect Tile::getRect()
{
    return drect;
}