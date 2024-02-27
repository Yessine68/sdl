#include "new_window.h"
#include <SDL/SDL_image.h>

SDL_Surface* createWindow(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* newScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption(title, NULL);

    // Load background image
    SDL_Surface* map = IMG_Load("map.png");
    SDL_BlitSurface(map, NULL, newScreen, NULL);
    SDL_FreeSurface(map);

    SDL_Flip(newScreen);
    return newScreen;
}
