#include "MainPlayer.hpp"
#include "TextureManager.h"

int cnt = 0;
int GameOver = 0;
MainPlayer::MainPlayer(const char* fileName, int h)
{
    objTexture = TextureManager::LoadTexture(fileName);
    height = h;
    // playerSpeed = s;
    xpos = 0;
    ypos = target = groundPos-40;
    // state = "OnGround";
    state = "Fall";
}

MainPlayer::~MainPlayer() {}

void MainPlayer::setState(string s)
{
    // if(state != "Fall" && state != "OnTile")
        state = s;
}

void MainPlayer::Update()
{
    cout << target << "   " << ypos << "   " << state << "   " << val << "   " << cnt << endl;
    cnt++;

    // if(groundPos-40 <= ypos && ypos <= groundPos)   state = "OnGround";
    // cout << ypos << endl;

    if(state == "OnTile")
    {
        ypos = tilePos;
    }
    else
    {
        if(state == "Jump")
            val = val-1;
        
        if(val == 0)
        {
            if(groundPos-40 <= ypos && ypos <= groundPos)   {target = level0Pos-40-40;}
            else if(level0Pos-40+15 >= ypos && ypos >= level0Pos-40-15-5)   target = level1Pos-40-40;
            else    target = level1Pos-170;
        }

        if(target<ypos && state != "Fall")
        {
            ypos = ypos-jumpHeight;
        }

        else
        {
            val = 1;
            state = "Fall";
            // target = ypos;
            // ypos = target;
        }

        if(state == "Fall" && ypos+40 < groundPos)
        {
            // cout << "Faaaaaaaaaaaaaaaallllllllllllliiiinnnnnnnnnnngggggggggg" << endl
            ypos = ypos+jumpHeight;
            
        }
    }

    // if(state == "Jump" && (ypos == groundPos || ypos == level0Pos || ypos == level1Pos) )
    // {
    //     // if(ypos == groundPos)
    //     // {
    //     //     ypos = ypos-jumpHeight;
    //     // }
    //     ypos = ypos - jumpHeight;
    // }

    // else if(ypos <= 300)
    // {
    //     state = "NULL";
    // }

    // if(state == "NULL" && ypos < 650)
    // {
    //     ypos = ypos + jumpHeight;
    // }

    srect.w = 64,
    srect.h = 64;
    srect.x = 0;
    srect.y = 0;

    drect.x = xpos;
    drect.y = ypos;
    drect.w = srect.w;
    drect.h = height;

    // cout << "Player - " << drect.x << " " << drect.y << " " << val << endl;
}

void MainPlayer::Render()
{
    // cout << "Rendering - " << ypos << endl;
    SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &drect, 0, NULL, SDL_FLIP_NONE);
}


void MainPlayer::landOn(int pos)
{
    // if(pos <= ypos)
    //     controlVal = -1;

    // ypos = pos-40;
    tilePos = pos-height-5;
    // if(state!="Jump")
       state = "OnTile";
    cout << "Changing the state from Jump to OnTile" << endl;
    // cout << "Collided - " << pos << endl;
}