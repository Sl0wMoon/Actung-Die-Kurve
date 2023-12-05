#include "SDL.h"
#include <iostream>
#include <string>
#include "Snake.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    Snake achtung;
    bool ingame = true;
    while (ingame == true) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    achtung.turnleft();
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    achtung.turnright();
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    ingame = false;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT && achtung.get_turn() == 1)
                    achtung.turnfwd();
                else if (event.key.keysym.sym == SDLK_RIGHT && achtung.get_turn() == -1)
                    achtung.turnfwd();
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (achtung.get_turn() != 0) {
            achtung.steer();
        }
        achtung.move();
        achtung.draw_snake(renderer);
        SDL_RenderPresent(renderer);
        if (achtung.get_turn() == 1)
            std::cout << "turning left" << std::endl;
        if (achtung.get_turn() == -1)
            std::cout << "turning right" << std::endl;

        SDL_Delay(8);
    }
	return 0;
}