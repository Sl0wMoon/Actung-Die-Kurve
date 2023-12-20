#include "SDL.h"
#include <iostream>
#include <string>
#include "Snake.h"
#include "test.h"
#include <random>
#include "Collision_manager.h"
#include "Score_system.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(50, 750);

    Collision_manager collision_manager;
    Score_system score_system;

    SDL_Color border_color = { 255, 255, 0, 255 };

    bool ingame = true;
    bool paused;
    float fps = 120;
    float delta_fps = 1000.0f / fps;
    int tick = 0;

    score_system.add_player({ 255 , 0 , 0 , 255 }, "achtung", SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    score_system.add_player({ 0 , 255 , 0 , 255 } , "kessel", SDL_SCANCODE_A, SDL_SCANCODE_D);
    auto players = score_system.get_players();
    while (ingame == true) { //loop for game
        paused = true;

        std::vector<Snake> snake_vector;
        for (auto it = players.begin(); it != players.end(); it++) {
            snake_vector.push_back(Snake(distribution(gen), distribution(gen), distribution(gen), it->color, it->left_key, it->right_key));
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        for (int i = 0; i < 5; i++) {
            SDL_Rect piss_border_rect = { 0 + i, 0 + i, 1200 + -2 * i, 900 + -2 * i };
            SDL_RenderDrawRect(renderer, &piss_border_rect);
        }

        score_system.init_round();
        while (ingame == true) { //loop for round
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
                snake_vector[i].handle_stop_draw(renderer, tick);
                snake_vector[i].check_collision(window, collision_manager.get_pixels());
                if (!snake_vector[i].is_alive()) {
                    snake_vector.erase(snake_vector.begin() + i);
                    score_system.add_score(snake_vector[i].get_color());
                    continue;
                }
                snake_vector[i].draw_snake(renderer);
            }
            if (SDL_GetTicks() - frame_time_start < delta_fps) {
                SDL_Delay(delta_fps - (SDL_GetTicks() - frame_time_start));
            }
            tick++;
            SDL_RenderPresent(renderer);
            if (snake_vector.size() == 1) {
                score_system.add_score(snake_vector[0].get_color());
            }
            if (snake_vector.size() < 1) {
                paused = !paused;
            }
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
            if (snake_vector.size() <= 1) {
                break;
            }
        }
    }
    return 0;
}
