#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "new_window.h"
#include "function.h"


int ScreenCleared = 0;


int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface *screen = SDL_SetVideoMode(1457, 817, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("SDL Background with Music", NULL);

    // Load background image
    background = IMG_Load("assets/background.png");
    cover = IMG_Load("assets/cover.png");
    // Load new window background image
    SDL_Surface *map = IMG_Load("assets/map.png");

    // Blit the background to the screen
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);

    // Initialize SDL_mixer
    if (!initMixer())
    {
        return 1;
    }
    loadHoverSound();
    loadSelectSound();

    // Load background music
    Mix_Music *music = Mix_LoadMUS("assets/son.mp3");

    // Play the background music indefinitely
    Mix_PlayMusic(music, -1);

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    // Initialize SDL_ttf
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("bold.ttf", 35); // Change "arial.ttf" to the path of your font file

    // Create a color for the text (black)
    SDL_Color textColor = {255, 255, 255};

    // Render text to surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello !", textColor);
    SDL_Surface *textSurfaceSettings = TTF_RenderText_Solid(font, "Settings", textColor);
    SDL_Surface *textSurfaceQuit = TTF_RenderText_Solid(font, "Quit", textColor);
    SDL_Surface *textSurfacePlay = TTF_RenderText_Solid(font, "Play", textColor);

    // Set the position of the text
    SDL_Rect textPosition;
    textPosition.x = 100;
    textPosition.y = 100;

    // Load button image
    SDL_Surface *button1 = IMG_Load("assets/button1_big.png");
    SDL_Rect buttonPosition1;
    buttonPosition1.x = 1000;
    buttonPosition1.y = 320;

    SDL_Surface *button2 = IMG_Load("assets/button2_big.png");
    SDL_Rect buttonPosition2;
    buttonPosition2.x = 930;
    buttonPosition2.y = 420;

    SDL_Surface *button3 = IMG_Load("assets/button3_big.png");
    SDL_Rect buttonPosition3;
    buttonPosition3.x = 985;
    buttonPosition3.y = 515;
    // Blit text onto the screen
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    SDL_Flip(screen);
    bool buttonClicked = false;

    // Main loop
    int quit = 0;
    int mouse_x, mouse_y;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEMOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                // Check if mouse is within the specified ranges
                if (mouse_x >= 1100 && mouse_x <= 1300 &&
                    mouse_y >= 360 && mouse_y <= 380)
                {
                    // Render button image
                    SDL_BlitSurface(button1, NULL, screen, &buttonPosition1);
                    SDL_BlitSurface(textSurfacePlay, NULL, screen, &textPosition);

                    SDL_Flip(screen);
                    playHoverSound();
                    stopSelectSound();
                    ScreenCleared = 0;
                }
                else if (mouse_x >= 971 && mouse_x <= 1211 &&
                         mouse_y >= 431 && mouse_y <= 475)
                {
                    stopHoverSound();
                    playSelectSound(); // Play select sound for button 2

                    // Render button image
                    SDL_BlitSurface(button2, NULL, screen, &buttonPosition2);
                    SDL_BlitSurface(textSurfaceSettings, NULL, screen, &textPosition);
                    SDL_Flip(screen);
                    ScreenCleared = 0;
                }
                else if (mouse_x >= 1000 && mouse_x <= 1370 &&
                         mouse_y >= 522 && mouse_y <= 566)
                {
                    stopHoverSound();
                    playSelectSound(); // Play select sound for button 2

                    // Render button image
                    SDL_BlitSurface(button3, NULL, screen, &buttonPosition3);
                    SDL_BlitSurface(textSurfaceQuit, NULL, screen, &textPosition);
                    SDL_Flip(screen);
                    ScreenCleared = 0;
                }
                else
                {
                    stopHoverSound();
                    stopSelectSound();
                    if (ScreenCleared >= 0 && (ScreenCleared < 2))
                    {
                        ScreenCleared++;
                    }
                    if (ScreenCleared >= 1)
                    {
                        SDL_BlitSurface(cover, NULL, screen, NULL);
                    }

                    // Clear button image
                    SDL_BlitSurface(background, &buttonPosition1, screen, &buttonPosition1);
                    SDL_BlitSurface(background, &buttonPosition2, screen, &buttonPosition2);
                    SDL_BlitSurface(background, &buttonPosition3, screen, &buttonPosition3);

                    SDL_Flip(screen);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (mouse_x >= 1100 && mouse_x <= 1300 &&
                    mouse_y >= 360 && mouse_y <= 380)
                {
                    displayImages(screen);
                    buttonClicked = true;
                }
                else if (mouse_x >= 971 && mouse_x <= 1211 &&
                         mouse_y >= 431 && mouse_y <= 475)
                {
                    handleSettings(screen);
                }
                else if (mouse_x >= 1000 && mouse_x <= 1370 &&
                         mouse_y >= 522 && mouse_y <= 566)
                {
                    quit = 1;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q)
                {
                    // Quit the application
                    quit = 1;
                }
                else if (event.key.keysym.sym == SDLK_p)
                {
                    displayImages(screen);
                    buttonClicked = true;
                }
                else if (event.key.keysym.sym == SDLK_s)
                {
                    handleSettings(screen);
                }
            }
        }

        if (buttonClicked)
        {
            SDL_Surface *newWindow = createWindow("New Window", 1457, 817);

            // Delay for demonstration purposes (optional)
            SDL_Delay(3000);

            SDL_FreeSurface(newWindow);
        }
    }

    // Cleanup
    //  Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_FreeSurface(background);
    // SDL_FreeSurface(textSurface);
    SDL_FreeSurface(button1);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
