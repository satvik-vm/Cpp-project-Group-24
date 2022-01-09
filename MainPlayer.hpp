#pragma once

#include "Game.hpp"
#include<string.h>

class MainPlayer
{
    public:
        MainPlayer(const char*, int);
        ~MainPlayer();
        int getX() {return xpos;}
        int getY() {return ypos;}
        int getHeight() {return height;}
        void Update();
        void Render();
        // void handleEvent(SDL_Event);
        // void Jump();
        void setState(string);
        string getState() {return state;}
        SDL_Rect getRect() {return drect;}
        void landOn(int);
        // int Targetty=420-80;

    private:
        int xpos, ypos, height;
        SDL_Texture* objTexture;
        SDL_Rect srect, drect;
        // int playerSpeed;
        int jumpHeight = 10;
        string state;
        // int groundPos = 750, level0Pos = 425, level1Pos = 200;
        int groundPos = 922-170, level0Pos = 590-170, level1Pos = 366-170;
        int val = 1;
        int target;
        int controlVal=1;
        int tilePos;
};