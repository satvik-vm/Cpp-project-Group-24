#include "MysteryBox.hpp"
#include "Game.hpp"
#include "TextureManager.h"

MysteryBox::MysteryBox(const char* fileName, int x, int y, int t)
{
    objTexture = TextureManager::LoadTexture(fileName);//Loading the image

    //Setting the x position, y position and the type of the box
    xpos = x+10;
    ypos = y-30;
    type = t;
}

MysteryBox::~MysteryBox() {

    xpos = 100000;
    ypos = 100000;
}

void MysteryBox::Update(int speed)
{
    xpos = xpos-speed;

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;
   
    drect.x = xpos;
    drect.y = ypos;
    drect.w = srect.w/2;
    drect.h = srect.h/2;
}

void MysteryBox::Render()
{
    if(val)
        SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_NONE);
}

int MysteryBox::isTouched()
{
    val = 0;
    if (type == 1)
        return 1;
    else
        return 0;
}

int MysteryBox::getX()
{
    return xpos;
}

int MysteryBox::getY()
{
    return ypos;
}

SDL_Rect MysteryBox::getRect()
{
    return drect;
}