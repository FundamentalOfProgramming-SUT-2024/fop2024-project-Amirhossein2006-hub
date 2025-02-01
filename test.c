#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void initialize_SDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

void close_SDL() {
    Mix_CloseAudio();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    initialize_SDL();

    Mix_Music* bgm = Mix_LoadMUS("music.mp3");
    // if (bgm == NULL) {
    //     printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    //     close_SDL();
    //     return 1;
    // }

    Mix_PlayMusic(bgm, -1);
    // printf("Music is playing in the background...\n");

    // Initialize ncurses
    initscr();
    // cbreak();
    noecho();
    //timeout(-1); // Wait indefinitely for a key press

    int quit = 0;

    while (!quit) {
        int ch = getch();
        switch (ch) {
            case 's':
                Mix_PauseMusic();
                printw("Music paused\n");
                break;
            case 'r':
                Mix_ResumeMusic();
                printw("Music resumed\n");
                break;
            case 'q':
                quit = 1;
                break;
        }
        refresh();
    }

    // Clean up ncurses
    endwin();

    Mix_FreeMusic(bgm);
    close_SDL();

    return 0;
}
