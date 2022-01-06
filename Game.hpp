#ifndef Game_hpp
#define Game_hpp

#include<SDL2/SDL.h>
#include"SDL2/SDL_image.h"
#include"SDL2/SDL_ttf.h"
#include"SDL2/SDL_mixer.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

class Game{
    private:
        bool isRunning;
        SDL_Window *window;
        int val = 5000;
        int screenWidth;
        int screenHeight;
        int speed = 0;

    public:
        Game();
        ~Game();
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();
        static SDL_Renderer *renderer;
        bool isCollided(SDL_Rect a, SDL_Rect b);
        bool isCollidedF(SDL_FRect, SDL_FRect);
        void Set_Gamerunning(bool x);
        int Show_menu(int choice);
        void show_instructions();
        int LoadingMenu();
        TTF_Font *font = NULL;
        TTF_Font *font1 = NULL;
        SDL_Color WHITE = {255, 255, 255};
        SDL_Color RED = {255, 0, 0};
        SDL_Color GREEN = {0, 255, 0};
        SDL_Color ORANGE = {255, 155, 0};
        SDL_Color ORANGERED = {255, 69, 0};
        int LeaderBoard();
        bool myCmp(string, string);
};


#endif