#include "function.h"
#include "new_window.h"
#include <stdio.h>

bool hoverSoundPlayed = false;
bool selectSoundPlayed = false;
SDL_Surface *background = NULL;
SDL_Surface *cover = NULL;
SDL_Rect backgroundPosition = {0, 0, 0, 0};
Mix_Chunk *hoverSound = NULL;
Mix_Chunk *selectSound = NULL;

bool initMixer()
{
    // Initialize SDL_mixer
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1)
    {
        printf("Unable to initialize SDL_mixer! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}
void displayImages(SDL_Surface *screen)
{
    SDL_Surface *image;
    char filename[50]; // Increased buffer size to accommodate the folder path

    for (int i = 0; i < 10; ++i)
    {
        // Construct filename for each image with the folder path
        snprintf(filename, sizeof(filename), "assets/background%d.jpg", i); // Use snprintf to prevent buffer overflow

        // Load image
        image = IMG_Load(filename);

        // Check if image loaded successfully
        if (image == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
            continue;
        }

        // Blit image to screen
        SDL_BlitSurface(image, NULL, screen, NULL);
        SDL_Flip(screen);

        // Free image surface
        SDL_FreeSurface(image);

        // Delay for 0.5 seconds
        SDL_Delay(500); // Adjusted delay to 500 milliseconds
    }
}
void loadHoverSound()
{
    // Load hover sound
    hoverSound = Mix_LoadWAV("assets/play.wav");
    if (hoverSound == NULL)
    {
        printf("Unable to load sound bas.wav! SDL_mixer Error: %s\n", Mix_GetError());
    }
}
void loadSelectSound()
{
    // Load select sound
    selectSound = Mix_LoadWAV("assets/select_short.wav");
    if (selectSound == NULL)
    {
        printf("Unable to load sound select.wav! SDL_mixer Error: %s\n", Mix_GetError());
    }
}
void playHoverSound()
{
    // If the hover sound has already been played or not loaded, return
    if (hoverSoundPlayed || hoverSound == NULL)
    {
        return;
    }

    // Play hover sound once
    int channel = Mix_PlayChannel(-1, hoverSound, 0);
    if (channel == -1)
    {
        printf("Unable to play sound bas.wav! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Set the flag to true to indicate that the sound has been played
    hoverSoundPlayed = true;
}
void stopHoverSound()
{
    // Stop playing the sound
    if (hoverSoundPlayed)
    {
        Mix_HaltChannel(-1);
        hoverSoundPlayed = false;
    }
}
void playSelectSound()
{
    // Play select sound once
    // If the hover sound has already been played or not loaded, return
    if (selectSoundPlayed || selectSound == NULL)
    {
        return;
    }

    // Play hover sound once
    int channel = Mix_PlayChannel(-1, selectSound, 0);
    if (channel == -1)
    {
        printf("Unable to play sound bas.wav! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Set the flag to true to indicate that the sound has been played
    selectSoundPlayed = true;
}
void stopSelectSound()
{
    // Stop playing the sound
    if (selectSoundPlayed)
    {
        Mix_HaltChannel(-1);
        selectSoundPlayed = false;
    }
}

void handleSettings(SDL_Surface *screen)
{
    // Load background image
    SDL_Surface *settingsBackground = IMG_Load("assets/background1.jpg");
    if (settingsBackground == NULL)
    {
        printf("Failed to load background image: %s\n", IMG_GetError());
        return;
    }

    // Load button images
    SDL_Surface *buttonFullscreen = IMG_Load("assets/full.png");
    SDL_Surface *buttonWindowed = IMG_Load("assets/window.png");
    SDL_Surface *buttonPlus = IMG_Load("assets/inc_volume.png");
    SDL_Surface *buttonMinus = IMG_Load("assets/dec_volume.png");
    SDL_Surface *buttonBack = IMG_Load("assets/back.png");

    if (buttonFullscreen == NULL || buttonWindowed == NULL)
    {
        printf("Failed to load button images: %s\n", IMG_GetError());
        SDL_FreeSurface(settingsBackground); // Free the background surface
        return;
    }

    // Set the initial position of the background and buttons
    SDL_Rect settingsPosition = {0, 0, 0, 0};
    SDL_Rect buttonFullscreenPosition = {100, 200, 0, 0};
    SDL_Rect buttonWindowedPosition = {100, 400, 0, 0};
    SDL_Rect buttonPlusVolPosition = {1000, 200, 0, 0};
    SDL_Rect buttonMinusVolPosition = {1000, 400, 0, 0};
    SDL_Rect buttonBackPosition = {1100, 600, 0, 0};
    // Blit the background and buttons to the screen
    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
    SDL_BlitSurface(buttonPlus, NULL, screen, &buttonPlusVolPosition);
    SDL_BlitSurface(buttonMinus, NULL, screen, &buttonMinusVolPosition);
    SDL_BlitSurface(buttonBack, NULL, screen, &buttonBackPosition);
    SDL_Flip(screen);

    bool settingsPage = true;
    SDL_Event event;
    while (settingsPage)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                settingsPage = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                if (mouse_x >= 100 && mouse_x <= 300 &&
                    mouse_y >= 200 && mouse_y <= 300)
                {
                    // Set fullscreen mode
                    SDL_WM_ToggleFullScreen(screen);
                    // Redraw the background after changing the screen mode
                    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
                    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
                    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
                    SDL_BlitSurface(buttonPlus, NULL, screen, &buttonPlusVolPosition);
                    SDL_BlitSurface(buttonMinus, NULL, screen, &buttonMinusVolPosition);
                    SDL_BlitSurface(buttonBack, NULL, screen, &buttonBackPosition);
                    SDL_Flip(screen);
                }
                else if (mouse_x >= 100 && mouse_x <= 300 &&
                         mouse_y >= 400 && mouse_y <= 500)
                {
                    // Set windowed mode
                    SDL_SetVideoMode(1457, 817, 32, SDL_SWSURFACE);
                    // Redraw the background after changing the screen mode
                    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
                    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
                    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
                    SDL_BlitSurface(buttonPlus, NULL, screen, &buttonPlusVolPosition);
                    SDL_BlitSurface(buttonMinus, NULL, screen, &buttonMinusVolPosition);
                    SDL_BlitSurface(buttonBack, NULL, screen, &buttonBackPosition);
                    SDL_Flip(screen);
                }
                else if (mouse_x >= 1200 && mouse_x <= 1400 &&
                         mouse_y >= 600 && mouse_y <= 700)
                {
                    // Quit the application
                    settingsPage = false;
                    SDL_BlitSurface(background, NULL, screen, &backgroundPosition);
                    SDL_Flip(screen);
                }
                else if (mouse_x >= 1000 && mouse_x <= 1300 &&
                         mouse_y >= 200 && mouse_y <= 300)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) + 10);
                    printf("volume increased \n");
                }
                else if (mouse_x >= 1000 && mouse_x <= 1300 &&
                         mouse_y >= 400 && mouse_y <= 500)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) - 10);
                    printf("volume decreased \n");
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_b)
                {
                    // Quit the application
                    settingsPage = false;
                    SDL_BlitSurface(background, NULL, screen, &backgroundPosition);
                    SDL_Flip(screen);
                }
                else if (event.key.keysym.sym == SDLK_w)
                {
                    SDL_SetVideoMode(1457, 817, 32, SDL_SWSURFACE);
                    // Redraw the background after changing the screen mode
                    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
                    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
                    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
                    SDL_BlitSurface(buttonPlus, NULL, screen, &buttonPlusVolPosition);
                    SDL_BlitSurface(buttonMinus, NULL, screen, &buttonMinusVolPosition);
                    SDL_BlitSurface(buttonBack, NULL, screen, &buttonBackPosition);
                    SDL_Flip(screen);
                }
                else if (event.key.keysym.sym == SDLK_f)
                {
                    SDL_WM_ToggleFullScreen(screen);
                    // Redraw the background after changing the screen mode
                    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
                    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
                    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
                    SDL_BlitSurface(buttonPlus, NULL, screen, &buttonPlusVolPosition);
                    SDL_BlitSurface(buttonMinus, NULL, screen, &buttonMinusVolPosition);
                    SDL_BlitSurface(buttonBack, NULL, screen, &buttonBackPosition);
                    SDL_Flip(screen);
                }
                else if (event.key.keysym.sym == SDLK_p)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) + 10);
                    printf("volume increased \n");
                }
                else if (event.key.keysym.sym == SDLK_m)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) - 10);
                    printf("volume decreased \n");
                }
            }
        }
    }

    // Free the surface for the background and buttons after the loop exits
    SDL_FreeSurface(settingsBackground);
    SDL_FreeSurface(buttonFullscreen);
    SDL_FreeSurface(buttonWindowed);
}
