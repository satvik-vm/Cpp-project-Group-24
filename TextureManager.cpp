#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tmpSurface = IMG_Load(fileName);   //First, the image data is loaded onto a temporary surface...
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);    //...Then, a texture is created from the surface...
    SDL_FreeSurface(tmpSurface);    //...and then, the surface is freed...

    return tex; //...and finally, the texture is returned
}

SDL_Texture* TextureManager::LoadText(TTF_Font *font, const char* text, SDL_Color color)
{
    SDL_Surface* surf;  //A temporary surface is created
    surf = TTF_RenderText_Solid(font, text, color); //The information of the text is loaded onto this surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);  //A texture is created from this surface

    return tex; //And the texture is returned
}