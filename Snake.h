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
};

/*struct Curve {
	Twod a;
	Twod b;
	int spd;
	int steer;
	int direction;
	Curve() {
		a = Twod(0, 0);
		b = Twod(0, 0);
		spd = 0;
		steer = 0;
		direction = 0;
	}
	Curve(Twod first, Twod second, int speed, int direct, int str) {
		a = first;
		b = second;
		spd = speed;
		steer = str;
		direction = direct;
	}
};*/

class Snake
{
private:
	bool alive;
	int heading;
	double degreetorad(int degree);
	Twod position;
	Twod previous_position;
	Twod next_position;
	float amplitude;
	Twod speed;
	int steer_amount;
	int steer_multiplier;
	//Twod anchor;
	int draw_circle(SDL_Renderer* renderer, Twod point);
	std::vector<Uint32>* find_color(SDL_Window* window, Twod pos);
	//std::vector<Curve> trail; mentioned since I am no longer going to render the trail each frame.
	//void add_to_tail();
	//int draw_tail_part(SDL_Renderer* renderer, int posx, int posy);
	//void draw_tail(SDL_Renderer* renderer);
public:
	Snake(int heading, int xposition, int yposition);
	Snake();
	void check_collision(SDL_Window* window);
	void steer();
	void turnleft();
	void turnright();
	void turnfwd();
	int size;
	const bool is_alive();
	void move();
	int get_turn();
	Twod get_pos();
	void draw_snake(SDL_Renderer* renderer);
};

