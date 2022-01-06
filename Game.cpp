#include "Game.hpp"
#include "TextureManager.h"
#include "Witch.hpp"
#include "Lion.hpp"
#include "Tile.hpp"
#include "MysteryBox.hpp"
#include "Monkey.hpp"
#include "MainPlayer.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

vector<Lion *> lions;
vector<Tile *> tiles;
vector<MysteryBox *> boxes;
vector<Witch *> witches;
vector<SDL_Texture*> loadingWitches;
vector<SDL_Texture*> loadingPlayers;
vector<string> scores;
vector<Mix_Chunk *> sfx;
Mix_Music *music;
Monkey *monkey;
MainPlayer *mainPlayer;
SDL_Renderer *Game::renderer = nullptr;
SDL_Texture *bgImage0;
SDL_Rect bgRect0;
SDL_Texture *bgImage1;
SDL_Rect bgRect1;

int lionAttack = 0;
int monkeyAttack = 0;
int witchAttack = 0;
int newTile = 0;
long long int randomValLion;
long long int randomValMonkey;
int speed = 1;
int xMouse, yMouse;
int lives;
int Score = 0;
int initialTime;

// int tileYPos0 = 425, tileYPos1 = 200, tileXPos = 500, tileWidth = 400;
int tileYPos0 = 420, tileYPos1 = 196, tileXPos = 500, tileWidth = 400;

Game ::Game() {}

Game ::~Game() {}

void Game::Set_Gamerunning(bool x)
{
    isRunning = x;
}

void Game ::init(const char *title, int xipos, int yipos, int width, int height, bool fullscreen)
{
    initialTime = 0;
    lives = 5;

    srand((unsigned int)time(NULL));
    screenWidth = width;
    screenHeight = height;

    int flags = 0;

    if (flags)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystem succesfully created!" << endl;

        window = SDL_CreateWindow(title, xipos, yipos, width, height, flags);

        if (TTF_Init())
        {
            cout << "True type fonts initialized" << endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "SDL_mixer could not be initialized" << Mix_GetError() << endl;
        }

        if (window)
            cout << "Window created!" << endl;

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "Renderer succesfully created!" << endl;
        }

        isRunning = true;
    }
    bgImage0 = TextureManager::LoadTexture("sunrise2.jpg");
    bgImage1 = TextureManager::LoadTexture("sunrise2.jpg");
    bgRect0.x = bgRect0.y = bgRect1.y = 0;
    bgRect1.x = screenWidth;
    bgRect0.w = bgRect1.w = screenWidth;
    bgRect0.h = bgRect1.h = screenHeight;
    font=TTF_OpenFont("font.ttf",50);
    font1=TTF_OpenFont("font6.ttf",100); 


    for (int i = 0; i < 12; i++)
    {
        string s = "Lion" + to_string(i) + ".jpg";
        const char *c = s.c_str();
        lions.push_back(new Lion(c));
    }

    int type = rand() % 2;
    tiles.push_back(new Tile("TileResized.png", tileXPos, tileYPos0, tileWidth));
    boxes.push_back(new MysteryBox("mbox.png", tileXPos, tileYPos0, type));
    witches.push_back(new Witch("witch.png", tileXPos, tileYPos0, tileWidth, val % 1000));
    monkey = new Monkey("monkeyTransparent2.png", 800, -5, 200);
    mainPlayer = new MainPlayer("Player1.png", 40);
    Mix_Chunk *goodbox = Mix_LoadWAV("GoodBox.wav");
    Mix_Chunk *badbox = Mix_LoadWAV("BadBox.wav");
    Mix_Chunk *jump = Mix_LoadWAV("Jump.wav");
    sfx.push_back(jump);
    sfx.push_back(badbox);
    sfx.push_back(goodbox);
    music = Mix_LoadMUS("Music.wav");
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
}

void Game ::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
        isRunning = false;

    else if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            if (mainPlayer->getState() != "Jump")
            {
                mainPlayer->setState("Jump");
                Mix_PlayChannel(-1, sfx.at(0), 0);
                cout << "taking Up" << endl;
            }
            break;

        case SDLK_ESCAPE:
            while(1)
            {
                int i=Show_menu(1);
                if(i==0)
                    break;
                else if(i==1)
                    show_instructions();
                else if(i==2)
                {
                    isRunning=false;
                    break;
                }
            }
            break;

        default:
            break;
        }
    }
}

void Game::clean()
{
    Mix_FreeChunk(sfx.at(0));
    Mix_FreeMusic(music);
    music = NULL;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    SDL_Quit();

    cout << "Game cleaned!" << endl;
}

void Game ::update()
{
    if (mainPlayer->getState() == "Game Over")
    {
        clean();
        return;
    }
    val++;
    speed = int(val / 1000);

    randomValLion = rand();
    randomValMonkey = rand();

    if (newTile == 0 && tiles[tiles.size() - 1]->getX() + tileWidth <= screenWidth - 100)
    {
        newTile = 1;
    }

    if (newTile)
    {
        int type = rand() % 2;
        int mVal = (rand() % 2 == 0) ? tileYPos0 : tileYPos1;
        tiles.push_back(new Tile("TileResized.png", screenWidth, mVal, tileWidth));
        boxes.push_back(new MysteryBox("mbox.png", tiles[tiles.size() - 1]->getX(), mVal, type));
        witches.push_back(new Witch("witch.png", tiles[tiles.size() - 1]->getX(), mVal, tileWidth, speed));
        newTile = 0;
    }

    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i]->getX() > (-4) * tileWidth)
        {
            tiles[i]->Update(speed);
            boxes[i]->Update(speed);
            witches[i]->Update(speed);
        }
    }

    if (lionAttack == 0 && randomValLion % 100 <= 3 && lions[0]->getX() > -50 && SDL_GetTicks() % 1000 > 800)
    {
        for (int i = 0; i < 12; i++)
            lions[i]->setPos(screenWidth + 50);
        lionAttack = 1;
    }

    for (int i = 0; i < 12; i++)
    {
        lions[i]->Update(speed);
    }

    if (lions[0]->getX() < -50 && lionAttack == 1)
    {
        for (int i = 0; i < 12; i++)
            lions[i]->setPos(screenWidth + 50);
        lionAttack = 0;
    }

    if (monkeyAttack == 0 && randomValMonkey % 100 <= 3 && monkey->getX() > -50 && SDL_GetTicks() % 1000 > 800)
    {
        monkey->setPos(screenWidth);
        monkeyAttack = 1;
    }

    if (monkey->getX() < -10 && monkeyAttack == 1)
    {
        monkey->setPos(screenWidth);
        monkeyAttack = 0;
    }
    monkey->Update(speed);

    bgRect0.x -= speed;
    if (bgRect0.x <= (-1) * screenWidth)
        bgRect0.x = screenWidth;
    bgRect1.x -= speed;
    if (bgRect1.x <= (-1) * screenWidth)
        bgRect1.x = screenWidth;

    mainPlayer->Update();

    // cout << isCollided(mainPlayer->getRect(), lions[0]->getRect()) << endl;

    // if(isCollided(mainPlayer->getRect(), lions[0]->getRect()) || isCollided(mainPlayer->getRect(), monkey->getRect()) || isCollided(mainPlayer->getRect(), witch->getRect()))
    // {
    //     isRunning = true;
    //     // SDL_Delay(1200);
    // }

    int type;
    for (int i = 0; i < boxes.size(); i++)
    {
        if (isCollided(boxes[i]->getRect(), mainPlayer->getRect()))
        {
            type = boxes[i]->isTouched();
            if (type == 1)
            {
                Mix_PlayChannel(-1, sfx.at(1), 0);
                if (lives < 5)
                    lives++;
            }
            else
            {
                Mix_PlayChannel(-1, sfx.at(2), 0);
                Score += 10;
            }
            boxes[i]->~MysteryBox();
        }
    }


    for (int i = 0; i < witches.size(); i++)
    {
        if (isCollided(witches[i]->getRect(), mainPlayer->getRect()))
        {
            lives--;
            witches[i]->~Witch();
        }
    }
        if (isCollided(monkey->getRect(), mainPlayer->getRect()))
        {
            lives = 0;
            monkey->~Monkey();
        }
    

    for (int i = 0; i < lions.size(); i++)
    {
        if (isCollided(lions[i]->getRect(), mainPlayer->getRect()))
        {
            lives = 0;
            lions[i]->~Lion();
        }
    }

    for (int i = 0; i < tiles.size(); i++)
    {
        if(tiles[i]->getX()-60 <= mainPlayer->getX() && tiles[i]->getX()+tiles[i]->getWidth()+20 >= mainPlayer->getX() && tiles[i]->getY() >= mainPlayer->getY()+20 && tiles[i]->getY() <= mainPlayer->getY()+40)
        {
            mainPlayer->landOn(tiles[i]->getY());
            break;
        }

        else
        {
            if(mainPlayer->getState() == "OnTile")
                mainPlayer->setState("Fall");
        }
        
    }

    Score += (SDL_GetTicks() - initialTime) / 10000;
}

void Game ::render()
{
    if (lives > 0)
    {
        SDL_RenderClear(renderer);
        std::string livess = "Lives : " + to_string(lives);
        TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
        SDL_Color textColor = {255, 255, 255, 0};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, livess.c_str(), textColor);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
        int text_width = textSurface->w;
        int text_height = textSurface->h;
        SDL_Rect renderQuad = {10, 10, text_width, text_height};
        SDL_RenderCopy(Game::renderer, text, NULL, &renderQuad);
        SDL_RenderCopy(Game::renderer, bgImage0, NULL, &bgRect0);
        SDL_RenderCopy(Game::renderer, bgImage1, NULL, &bgRect1);

        for (int i = 0; i < tiles.size(); i++)
        {
            if (tiles[i]->getX() >= (-4) * tileWidth)
            {
                boxes[i]->Render();
                tiles[i]->Render();
                witches[i]->Render();
            }
        }

        if (lionAttack)
        {
            for (int i = 0; i < 12; i++)
            {
                if (SDL_GetTicks() % 12 == i)
                    lions[i]->Render();
            }
        }

        if (monkeyAttack)
            monkey->Render();

        SDL_Color Red = { 255,0,0 };
        SDL_Rect p1, p2;
        SDL_Surface* s = TTF_RenderText_Solid(font, "SCORE:", Red);
        SDL_Surface* s1 = TTF_RenderText_Solid(font, to_string(Score).c_str(), Red);
        p1.x = p1.y = p2.y = 0;
        p1.h = s->h;
        p1.w = s->w;
        p2.h = s1->h;
        p2.w = s1->w;
        p2.x = p1.x + p1.w;
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, s), NULL, &p1);
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, s1), NULL, &p2);


        string m = "X " + to_string(lives);
        const char* l = m.c_str();
        SDL_Surface* S = IMG_Load("health1.png");
        SDL_Surface* S1 = TTF_RenderText_Solid(font, l, Red);
        SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, S);
        SDL_Rect p, q;
        p.x = 0;
        p.y = 0 + 10 + p1.h;
        p.h = S1->h;
        p.w = 30;
        q.x = p.w + 5;
        q.y = p.y;
        q.h = S1->h;
        q.w = S1->w;
        SDL_RenderCopy(renderer, t, NULL, &p);
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, S1), NULL, &q);

        mainPlayer->Render();

        SDL_RenderPresent(renderer);
    }
    else
    {
        std::string score = "Score : " + to_string(Score);
        TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 40);
        SDL_Color textColor = {255, 255, 255, 0};
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, "GAME OVER", textColor);
        SDL_Surface *textSurface2 = TTF_RenderText_Blended(font, score.c_str(), textColor);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture *text2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
        int text_width = textSurface->w;
        int text_height = textSurface->h;
        int text_width2 = textSurface2->w;
        int text_height2 = textSurface2->h;
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(textSurface2);
        SDL_Rect renderQuad = {300, 300, text_width, text_height};
        SDL_Rect renderQuad2 = {700, 300, text_width2, text_height2};
        SDL_RenderCopy(renderer, text, NULL, &renderQuad);
        SDL_RenderCopy(renderer, text2, NULL, &renderQuad2);
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
        SDL_DestroyTexture(text);
        SDL_DestroyTexture(text2);
        isRunning = false;
        clean();
    }
}

bool Game::isCollided(SDL_Rect a, SDL_Rect b)   //Returns true if two Rects collide
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool Game::isCollidedF(SDL_FRect a, SDL_FRect b)    //Returns true if two FRects collide
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


bool Game ::running()
{
    return isRunning;
}


int Game::Show_menu(int choice)
{
    int x, y;
    const int size = 3;
    SDL_Surface *Menu[size];
    bool selected[size] = {false, false, false};
    const char *Labels[3] = {"Start Game", "Instructions", "Exit"};
    if (choice == 1)
        Labels[0] = "Resume Game";
    SDL_Color White = {255, 255, 255}, Red = {255, 0, 0};
    for (int i = 0; i < size; i++)
        Menu[i] = TTF_RenderText_Solid(font, Labels[i], White);
    SDL_Rect Position[size];
    Position[0].x = 400;
    Position[0].y = 400 - Menu[0]->h;
    Position[1].x = 400;
    Position[1].y = 420;
    Position[2].x = 400;
    Position[2].y = 440 + Menu[1]->h;
    for (int i = 0; i < size; i++)
    {
        Position[i].w = Menu[i]->w;
        Position[i].h = Menu[i]->h;
    }
    SDL_Surface *s = IMG_Load("image1.png");
    SDL_Texture *Texture = SDL_CreateTextureFromSurface(renderer, s);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Texture, NULL, NULL);
    for (int i = 0; i < size; i++)
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, Menu[i]), NULL, &Position[i]);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                for (int i = 0; i < size; i++)
                    SDL_FreeSurface(Menu[i]);
                return 2;
                break;

            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= Position[0].x && x <= Position[0].x + Position[0].w && y >= Position[0].y && y <= Position[0].y + Position[0].h)
                {
                    SDL_RenderClear(renderer);
                    return 0;
                }
                else if (x >= Position[1].x && x <= Position[1].x + Position[1].w && y >= Position[1].y && y <= Position[1].y + Position[1].h)
                {
                    return 1;
                }
                else if (x >= Position[2].x && x <= Position[2].x + Position[2].w && y >= Position[2].y && y <= Position[2].y + Position[2].h)
                {
                    SDL_RenderClear(renderer);
                    return 2;
                }
                break;
            }
        }
    }
}


void Game::show_instructions()
{
    int x, y;
    SDL_RenderClear(renderer);
    SDL_Surface *s = IMG_Load("instructions.png");
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_RenderCopy(renderer, t, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event event1;
    while (1)
    {
        while (SDL_PollEvent(&event1))
        {
            switch (event1.type)
            {
            case SDL_QUIT:
                SDL_FreeSurface(s);
                return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event1.motion.x;
                y = event1.motion.y;
                if (x >= 0 && x <= 70 && y >= 0 && y <= 80)
                {
                    SDL_FreeSurface(s);
                    return;
                }
                break;
            }
        }
    }
}


int Game::LoadingMenu()
{
    int gap = 10;

    SDL_Rect rect1;
    rect1.x = 150;
    rect1.y = 600;
    rect1.w = 900;
    rect1.h = 50;

    SDL_FRect rect2;
    rect2.x = rect1.x+gap;  
    rect2.y = rect1.y+gap;  
    rect2.w = 2;
    rect2.h = rect1.h-2*gap;

    SDL_FRect rect3;
    rect3.x = rect1.x+gap;
    rect3.y = rect1.y+gap;
    rect3.w = 0;
    rect3.h = rect1.h-2*gap;

    SDL_Rect loadingTextRect;
    loadingTextRect.x = rect1.x;
    loadingTextRect.y = rect1.y-rect1.h-20;
    loadingTextRect.w = 200;
    loadingTextRect.h = rect1.h;

    SDL_Rect jungleTextRect;
    jungleTextRect.w = 500;
    jungleTextRect.x = screenWidth/2-jungleTextRect.w/2;
    jungleTextRect.y = 100;
    jungleTextRect.h = 100;

    SDL_Rect runnerTextRect;
    runnerTextRect.w = 300;
    runnerTextRect.x = screenWidth/2-runnerTextRect.w/2;
    runnerTextRect.y = jungleTextRect.y+jungleTextRect.h+20;
    runnerTextRect.h = 100;

    for(int i=0;i<5;i++)
    {
        string s;
        s = "Player" + to_string(i) + ".png";
        const char* c = s.c_str();
        SDL_Texture* tempTex = TextureManager::LoadTexture(c);
        loadingPlayers.push_back(tempTex);
    }

    SDL_FRect playerRect;
    playerRect.h = 100;
    playerRect.y = rect2.y+rect2.h-playerRect.h;
    playerRect.w = 50;

    for(int i=0;i<5;i++)
    {
        string s;
        if(i==0) s = "ws0-removebg-preview-compressed.png";
        else  s = "ws" + to_string(5-i) + "-removebg-preview-compressed.png";

        const char* c = s.c_str();
        SDL_Texture* tempTex = TextureManager::LoadTexture(c);
        loadingWitches.push_back(tempTex);
    }

    SDL_FRect loadingWitchRect;
    loadingWitchRect.h = 100;
    loadingWitchRect.y = rect3.y+rect3.h-loadingWitchRect.h;
    loadingWitchRect.w = 50;
    loadingWitchRect.x = 100;

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    int val = 0;
    int cnt = 0;

    while(val != 1)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        const char* loading = "Loading...";
        const char* jungle = "FOREST";
        const char* runner = "RUNNER";
        SDL_RenderCopy(renderer, TextureManager::LoadText(font, loading, WHITE), NULL, &loadingTextRect);
        SDL_RenderCopy(renderer, TextureManager::LoadText(font, jungle, ORANGERED), NULL, &jungleTextRect);
        SDL_RenderCopy(renderer, TextureManager::LoadText(font, runner, GREEN), NULL, &runnerTextRect);

        SDL_RenderDrawRect(renderer, &rect1);

        if(rect2.w <= rect1.w-2*gap)
            rect2.w += 0.7;

        if(rect2.w >= rect1.w-2*gap)
        {
            if(rect3.w <= rect1.w-2*gap)
                rect3.w += 0.7;
        }

        playerRect.x = rect2.x+rect2.w;
        if(!(isCollidedF(loadingWitchRect, playerRect))) loadingWitchRect.x = rect3.x+rect3.w;
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRectF(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 255, 60, 0, 255);
        SDL_RenderFillRectF(renderer, &rect3);

        if(isCollidedF(loadingWitchRect, playerRect) && rect2.w >= rect1.w/2)
        {
            playerRect.y = rect1.y;
            SDL_RenderCopyExF(renderer, loadingPlayers[0], NULL, &playerRect, 90, NULL, SDL_FLIP_NONE);
        }

        else if(SDL_GetTicks()%250 < 50)
        {
            SDL_RenderCopyF(renderer, loadingPlayers[0], NULL, &playerRect);
        }

        else if(SDL_GetTicks()%250 < 100)
        {
            SDL_RenderCopyF(renderer, loadingPlayers[1], NULL, &playerRect);
        }

        else if(SDL_GetTicks()%250 < 150)
        {
            SDL_RenderCopyF(renderer, loadingPlayers[2], NULL, &playerRect);
        }

        else if(SDL_GetTicks()%250 < 200)
        {
            SDL_RenderCopyF(renderer, loadingPlayers[3], NULL, &playerRect);
        }

        else if(SDL_GetTicks()%200 < 250)
        {
            SDL_RenderCopyF(renderer, loadingPlayers[4], NULL, &playerRect);
        }

        if(rect3.w != 0 && !(isCollidedF(loadingWitchRect, playerRect)))
        {
            SDL_RenderCopyF(renderer, loadingWitches[0], NULL, &loadingWitchRect);
        }

        else if(rect3.w != 0)
        {
            if(SDL_GetTicks()%200 < 50)
                SDL_RenderCopyF(renderer, loadingWitches[1], NULL, &loadingWitchRect);

            else if(SDL_GetTicks()%200 < 100)
            SDL_RenderCopyF(renderer, loadingWitches[2], NULL, &loadingWitchRect);
            
            else if(SDL_GetTicks()%200 < 150)
            SDL_RenderCopyF(renderer, loadingWitches[3], NULL, &loadingWitchRect);
            
            else if(SDL_GetTicks()%200 < 200)
            {
                cnt++;
                SDL_RenderCopyF(renderer, loadingWitches[4], NULL, &loadingWitchRect);
            }
            
            if(cnt > 30)
            {
                SDL_Delay(1500);
                val = 1;
            }

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            isRunning = false;
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
        }
    }
    return 1;
}