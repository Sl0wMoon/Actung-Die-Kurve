#include "SDL.h"
#include <iostream>
#include <string>
#include "Snake.h"
#include "test.h"
#include <random>
#include "Collision_manager.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(10, 790);

    Collision_manager collision_manager;

    Snake achtung(-4, distribution(gen), distribution(gen), {255, 0,0 ,255}, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    Snake kessel(distribution(gen), distribution(gen), distribution(gen), {0, 0,255 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    Snake slow(distribution(gen), distribution(gen), distribution(gen), {0, 255,0 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    Snake slow2(distribution(gen), distribution(gen), distribution(gen), {0, 255,0 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    Snake slow3(distribution(gen), distribution(gen), distribution(gen), {0, 255,0 ,255}, SDL_SCANCODE_A, SDL_SCANCODE_D);
    std::vector<Snake> snake_vector;
    snake_vector.push_back(achtung);
    snake_vector.push_back(kessel);
    snake_vector.push_back(slow);
    snake_vector.push_back(slow2);
    snake_vector.push_back(slow3);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int i = 0; i < 5; i++) {
        SDL_Rect piss_border_rect = { 0 + i, 0 + i, 1600 + -2 * i, 900 + -2 * i };
        SDL_RenderDrawRect(renderer, &piss_border_rect);
    }


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    bool ingame = true;
    bool paused = true;
    float fps = 120;
    float delta_fps = 1000.0f / fps;
    while (ingame == true) {
        int frame_time_start = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    ingame = false;
                case SDLK_SPACE:
                    paused = !paused;
                }
            }
        }
        collision_manager.update_pixels(window);
        for (int i = 0; i < snake_vector.size(); i++) {
            snake_vector[i].handle_input(renderer);
            snake_vector[i].steer();
            snake_vector[i].move();
            snake_vector[i].check_collision(window, collision_manager.get_pixels());
            if (!snake_vector[i].is_alive()) {
                snake_vector.erase(snake_vector.begin() + i);
                continue;
            }
            snake_vector[i].draw_snake(renderer);
        }
        if (SDL_GetTicks() - frame_time_start < delta_fps) {
            SDL_Delay(delta_fps - (SDL_GetTicks() - frame_time_start));
        }
        SDL_RenderPresent(renderer);
        while (paused && ingame) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        ingame = false;
                    case SDLK_SPACE:
                        paused = !paused;
                    }
                }
            }
        }
    }
    return 0;
}
