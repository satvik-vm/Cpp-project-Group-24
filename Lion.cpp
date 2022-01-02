#include "Lion.hpp"

Lion::Lion(const char* fileName)
{
    objTexture = TextureManager::LoadTexture(fileName); //Loading the image

    lionSpeed = 4;
    basePos = 1000;
}

void Lion::Update(int speed)
{
    basePos = basePos - lionSpeed - speed;        //Decrementing the X value of the Lion by "speed" as well as by "lionSpeed".

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;

    drect.x = basePos;
    drect.y = 736;
    drect.w = srect.w;
    drect.h = srect.h;
}

void Lion::Render()
{
    SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void Lion::setPos(int pos)
{
    basePos = pos;
}

int Lion::getX() 
{
    return basePos;
}

SDL_Rect Lion::getRect()
{
    return drect;
}