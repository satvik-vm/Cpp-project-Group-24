#include "Game.hpp"
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Game *game = nullptr;

int main(int argc, char **argv)
{
	Game *game = new Game();
	const int FPS = 30;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	game->init("Jungle Survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);
	//sagar
	int choice=-1;
	while(1)
    {
        choice=game->Show_menu(0);
        if(choice==0)
            break;
        else if(choice==1)
            game->show_instructions();
        else if(choice==2)
        {
            game->Set_Gamerunning(false);
            break;
        }
    }
    //
	while(game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->clean();

	return 0;
}
