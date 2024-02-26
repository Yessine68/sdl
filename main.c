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
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Change "your_font.ttf" to the path of your font file

    // Create a color for the text (white)
    SDL_Color textColor = {255, 255, 255};

    // Render text to surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YAAW", textColor);

    // Set the position of the text
    SDL_Rect textPosition;
    textPosition.x = 1010;
    textPosition.y = 317;

    // Blit text onto the screen
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    SDL_Flip(screen);

    // Main loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_FreeSurface(background);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
