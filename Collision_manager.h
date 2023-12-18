#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>
class Collision_manager
{
private:
	Uint32* pixel;
public:
	Collision_manager();
	void update_pixels(SDL_Window* window);
	inline Uint32* get_pixels() { return pixel; }
};

