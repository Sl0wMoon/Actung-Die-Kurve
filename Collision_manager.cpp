#include "Collision_manager.h"


Collision_manager::Collision_manager() {
	pixel = new Uint32[1600 * 900];
}


void Collision_manager::update_pixels(SDL_Window* window) {
	SDL_RenderReadPixels(SDL_GetRenderer(window), NULL, SDL_PIXELFORMAT_RGB888, pixel, 1600 * sizeof(Uint32));
}