#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tmpSurface = IMG_Load(fileName);   //The image data is loaded onto a temporary surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);    //Then a texture, using this data, is created from the surface
    SDL_FreeSurface(tmpSurface);    //Finally, the temporary surface is freed...

    return tex; //...the texture is returned
}