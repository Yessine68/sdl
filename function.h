#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>

extern bool hoverSoundPlayed;
extern bool selectSoundPlayed;
extern SDL_Surface *background;
extern SDL_Surface *cover;
extern SDL_Rect backgroundPosition;
extern Mix_Chunk *hoverSound;
extern Mix_Chunk *selectSound;
extern int ScreenCleared;

bool initMixer();
void displayImages(SDL_Surface *screen);
void loadHoverSound();
void loadSelectSound();
void playHoverSound();
void stopHoverSound();
void playSelectSound();
void stopSelectSound();
void handleSettings(SDL_Surface *screen);

#endif /* FUNCTION_H_ */
