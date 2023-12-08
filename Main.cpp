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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    bool ingame = true;
    float fps = 120;
    float delta_fps = 1000.0f / fps;
    while (ingame == true) {
        int frame_time_start = SDL_GetTicks();
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
        
        achtung.steer();
        achtung.check_collision(window);
        achtung.move();
        achtung.draw_snake(renderer);
        SDL_RenderPresent(renderer);
        //if (achtung.get_turn() == 1)
            //std::cout << "turning left" << std::endl;
        //if (achtung.get_turn() == -1)
            //std::cout << "turning right" << std::endl;
        /*if (SDL_GetTicks() % 100 == 0) {
            std::cout << 1000.0 / (SDL_GetTicks() - frame_time_start) << "FPS" << std::endl;
        }*/
        if (SDL_GetTicks() - frame_time_start < delta_fps) {
            SDL_Delay(delta_fps - (SDL_GetTicks() - frame_time_start));
        }
        if (!achtung.is_alive()) {
            ingame = false;
        }
    }
	return 0;
}