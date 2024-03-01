#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "new_window.h"
bool hoverSoundPlayed = false;
bool selectSoundPlayed = false;
SDL_Surface *background = NULL;
SDL_Rect backgroundPosition = {0, 0, 0, 0};
Mix_Chunk *hoverSound = NULL;  // Define hover sound globally
Mix_Chunk *selectSound = NULL; // Define select sound globally

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

    // Blit the background and buttons to the screen
    SDL_BlitSurface(settingsBackground, NULL, screen, &settingsPosition);
    SDL_BlitSurface(buttonFullscreen, NULL, screen, &buttonFullscreenPosition);
    SDL_BlitSurface(buttonWindowed, NULL, screen, &buttonWindowedPosition);
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
                    SDL_Flip(screen);
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_q)
                {
                    // Quit the application
                    settingsPage = false;
                    SDL_BlitSurface(background, NULL, screen, &backgroundPosition);
                    SDL_Flip(screen);
                }
            }
        }
    }

    // Free the surface for the background and buttons after the loop exits
    SDL_FreeSurface(settingsBackground);
    SDL_FreeSurface(buttonFullscreen);
    SDL_FreeSurface(buttonWindowed);
}







int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface *screen = SDL_SetVideoMode(1457, 817, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("SDL Background with Music", NULL);

    // Load background image
    background = IMG_Load("assets/background.png");

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
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24); // Change "arial.ttf" to the path of your font file

    // Create a color for the text (black)
    SDL_Color textColor = {0, 0, 0};

    // Render text to surface
    // SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YAAW", textColor);

    // Set the position of the text
    SDL_Rect textPosition;
    textPosition.x = 1100;
    textPosition.y = 360;

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
    //  SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    //  SDL_Flip(screen);
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
                    SDL_Flip(screen);
                    playHoverSound();
                    stopSelectSound();
                }
                else if (mouse_x >= 971 && mouse_x <= 1211 &&
                         mouse_y >= 431 && mouse_y <= 475)
                {
                    stopHoverSound();
                    playSelectSound(); // Play select sound for button 2

                    // Render button image
                    SDL_BlitSurface(button2, NULL, screen, &buttonPosition2);
                    SDL_Flip(screen);
                }
                else if (mouse_x >= 1000 && mouse_x <= 1370 &&
                         mouse_y >= 522 && mouse_y <= 566)
                {
                    stopHoverSound();
                    playSelectSound(); // Play select sound for button 2

                    // Render button image
                    SDL_BlitSurface(button3, NULL, screen, &buttonPosition3);
                    SDL_Flip(screen);
                }
                else
                {
                    stopHoverSound();
                    stopSelectSound();
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
