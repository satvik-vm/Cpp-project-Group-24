#include "Witch.hpp"
#include "TextureManager.h"
using namespace std;

Witch::Witch(const char* fileName, int x, int y, int width, int speed)
{
    srand((unsigned int)time(NULL));

    objTexture = TextureManager::LoadTexture(fileName);
    
    tileWidth = width;
    minPos = x;
    xpos = x + (rand()%(width));
    ypos = y-30;
    val = speed*(-1);
    tileYPos = y;
}

Witch::~Witch()
{
    xpos = 100000;
    ypos = 100000;
}

void Witch::Update(int speed)
{
    minPos = minPos - abs(speed);

    if(xpos <= minPos+tileWidth && xpos >= minPos+buffer+32)
    {
        if(val < 0)   xpos = xpos+(val*2);
        else    xpos = xpos+(val)-speed;
    }
    else
    {
        val = val*(-1);
        if(xpos <= minPos+buffer+32)  xpos = minPos+buffer+5+32;//The speed with which it moves towards the left extreme
        if(xpos >= minPos+tileWidth-32)  xpos = minPos+tileWidth-32;//The speed with which it moves towards the right extreme
    }
    if(ypos <= tileYPos-35)
    {
        state = "Down";
    }
    if(ypos >= tileYPos-30)
    {
        state = "Up";
    }

    ypos += (state == "Down") ? 1 : -1;

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;

    drect.x = xpos;
    drect.y = ypos;
    drect.w = srect.w/2;
    drect.h = srect.h/2;
}

void Witch::Render()
{
    if(val > 0)
        SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_HORIZONTAL);
}

SDL_Rect Witch::getRect()
{
    return drect;
}