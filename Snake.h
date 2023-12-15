#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>

struct Twod {
	double x;
	double y;
	Twod() {
		x = 800;
		y = 450;
	}
	Twod(double px, double py) {
		x = px;
		y = py;
	}
	Twod operator+(const Twod & other) const {
		Twod result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;
		return result;
	}
};


class Snake
{
private:
	SDL_Color snake_color;
	SDL_Color trail_color;
	SDL_Color head_color;
	int left_key;
	int right_key;
	bool alive;
	int heading;
	double degreetorad(int degree);
	Twod position;
	Twod previous_position;
	float amplitude;
	Twod speed;
	int steer_amount;
	int steer_multiplier;
	Twod make_heading_vect(int heading);
	void draw_rotated_rect(SDL_Renderer* renderer, SDL_Rect rect, double angle);
	void stop_draw(SDL_Renderer * renderer);
	void start_draw(SDL_Renderer* renderer);
	int draw_circle(SDL_Renderer* renderer, Twod point);
	SDL_Color find_color(SDL_Window* window, Twod pos);
public:
	Snake(int heading, int xposition, int yposition, SDL_Color snake_color, int left, int right);
	Snake();
	void check_collision(SDL_Window* window);
	void handle_input(SDL_Renderer * renderer);
	void steer();
	void turn_left();
	void turn_right();
	void turn_fwd();
	int size;
	const bool is_alive();
	void move();
	int get_turn();
	Twod get_pos();
	void draw_snake(SDL_Renderer* renderer);
};

