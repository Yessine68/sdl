#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface* screen = SDL_SetVideoMode(1457, 817, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("SDL Background with Music", NULL);

    // Load background image
    SDL_Surface* background = IMG_Load("background1.png");

    // Blit the background to the screen
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);

    // Initialize SDL_mixer
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    // Load background music
    Mix_Music* music = Mix_LoadMUS("son.mp3");

    // Play the background music indefinitely
    Mix_PlayMusic(music, -1);

    // Initialize SDL_ttf
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Change "arial.ttf" to the path of your font file

    // Create a color for the text (black)
    SDL_Color textColor = {0, 0, 0};

    // Render text to surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YAAW", textColor);

    // Set the position of the text
    SDL_Rect textPosition;
    textPosition.x = 1100;
    textPosition.y = 360;

    // Load button image
    SDL_Surface* button = IMG_Load("button1.png");
    SDL_Rect buttonPosition;
    buttonPosition.x = 1100;
    buttonPosition.y = 360;

    // Blit text onto the screen
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    SDL_Flip(screen);

    // Main loop
    int quit = 0;
    int mouse_x, mouse_y;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION:
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    // Check if mouse is over the text
                    if (mouse_x >= textPosition.x && mouse_x <= textPosition.x + textSurface->w &&
                        mouse_y >= textPosition.y && mouse_y <= textPosition.y + textSurface->h) {
                        // Render button image
                        SDL_BlitSurface(button, NULL, screen, &buttonPosition);
                        SDL_Flip(screen);
                    } else {
                        // Clear button image
                        SDL_BlitSurface(background, &buttonPosition, screen, &buttonPosition);
                        SDL_Flip(screen);
                    }
                    break;
            }
        }
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_FreeSurface(background);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(button);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
