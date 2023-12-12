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
	SDL_Color color;
	SDL_Color head_color;
	SDL_Texture* filled_texture;
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
	//Twod anchor;
	int draw_circle(SDL_Renderer* renderer, Twod point);
	SDL_Color find_color(SDL_Window* window, Twod pos);
	//std::vector<Curve> trail; mentioned since I am no longer going to render the trail each frame.
	//void add_to_tail();
	//int draw_tail_part(SDL_Renderer* renderer, int posx, int posy);
	//void draw_tail(SDL_Renderer* renderer);
public:
	Snake(int heading, int xposition, int yposition);
	Snake();
	void check_collision(SDL_Window* window);
	void handle_input();
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

