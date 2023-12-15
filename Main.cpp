#include "SDL.h"
#include <iostream>
#include <string>
#include "Snake.h"
#include "test.h"
#include <random>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(10, 790);


    Snake achtung(distribution(gen), distribution(gen), distribution(gen), {255, 0,0 ,255}, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    Snake kessel(distribution(gen), distribution(gen), distribution(gen), {0, 0,255 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    Snake slow(distribution(gen), distribution(gen), distribution(gen), {0, 255,0 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    std::vector<Snake> snake_vector;
    snake_vector.push_back(kessel);
    snake_vector.push_back(achtung);
    snake_vector.push_back(slow);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    bool ingame = true;
    float fps = 60;
    float delta_fps = 1000.0f / fps;

    while (ingame == true) {
        int frame_time_start = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    ingame = false;
                }
            }
        }
        for (auto it = snake_vector.begin(); it != snake_vector.end(); it++) {
            it->handle_input(renderer);
            it->steer();
            it->move();
            it->check_collision(window);
            it->draw_snake(renderer);
            if (!it->is_alive()) {
                ingame = false;
            }
        }
        if (SDL_GetTicks() - frame_time_start < delta_fps) {
            SDL_Delay(delta_fps - (SDL_GetTicks() - frame_time_start));
        }
        SDL_RenderPresent(renderer);
        
    }
    return 0;
}
