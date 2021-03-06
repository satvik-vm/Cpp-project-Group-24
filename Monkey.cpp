#include "Monkey.hpp"
#include "TextureManager.h"
using namespace std;

Monkey::Monkey(const char* fileName, int x, int y, int h)
{
    objTexture = TextureManager::LoadTexture(fileName);//Loading the image

     //Setting the X position, Y position, and the height parameters of the monkey
    xpos = x;
    ypos = y;
    height = h;
}

Monkey::~Monkey()   {}

void Monkey::Update(int speed)
{
    angle = angle+1.0;//Increasing the angle by 1 unit
    xpos = xpos-2-speed;//Decrementing the X coordinate of the monkey by "speed" as well as by "monkeySpeed"

    // cout << "Angle - " << angle << endl;

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;

    drect.x = xpos;
    drect.y = ypos;
    drect.w = srect.w;
    drect.h = srect.h;
}

void Monkey::Render()
{
    hingePoint.x = 0;
    hingePoint.y = 0;
    if(angle<=160.0)
        SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, angle, &hingePoint, SDL_FLIP_NONE);
}

int Monkey::getX()
{
    return xpos;
}

int Monkey::getY()
{
    return ypos;
}

int Monkey::getHeight()
{
    return height;
}

SDL_Rect Monkey::getRect()
{
    return drect;
}

void Monkey::setPos(int pos)
{
    xpos = pos;
    angle = -100;
}