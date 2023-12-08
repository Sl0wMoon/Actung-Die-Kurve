#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>

class test
{
public:
    test() {}
    // Function to get the color of a pixel at a specific location
    bool getPixelColor(SDL_Surface* surface, int x, int y, Uint8& r, Uint8& g, Uint8& b) {
        // Make sure the surface is valid
        if (surface == nullptr) {
            return false;
        }

        // Get the pixel at the specified location
        Uint32 pixel = 0;
        Uint8* pixels = (Uint8*)surface->pixels;

        // Calculate the index of the pixel in the pixel array
        int index = y * surface->pitch + x * surface->format->BytesPerPixel;

        // Get the pixel value
        memcpy(&pixel, &pixels[index], surface->format->BytesPerPixel);

        // Get RGB components from the pixel value
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);

        return true;
    }

    int main() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL initialization failed: %s", SDL_GetError());
            return -1;
        }

        // Create a window and renderer
        SDL_Window* window = SDL_CreateWindow("Pixel Color Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Create a surface (you might load an image here instead)
        SDL_Surface* surface = SDL_GetWindowSurface(window);

        // Set a pixel at position (100, 100) to red
        SDL_SetRenderDrawColor(renderer, 0,0,255, 0);
        SDL_RenderDrawPoint(renderer,100,100);
    
        // Get the color of the pixel at position (100, 100)
        Uint8* color = new Uint8;
        *color = 1;
        SDL_RenderReadPixels(renderer, new SDL_Rect({ 100, 100 , 1, 1 }), SDL_PIXELFORMAT_RGBA8888, color, surface->format->BytesPerPixel);
        SDL_Color c = { -1,-1,-1,-1 };
        SDL_GetRGBA(*color, surface->format, &c.r, &c.g, &c.b, &c.a);
        std::cout << c.r << c.g << c.b << c.a;
        // Main loop
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            // Render stuff here if needed

            SDL_RenderPresent(renderer);
        }

        // Cleanup and exit
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }
};

