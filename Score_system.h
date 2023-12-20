#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>


struct Player {
	std::string name;
	int score;
	SDL_Color color;
	Player() {
		name = "unnamed";
		score = 0;
		color = { 255, 255, 255, 255 };
	}
	Player(SDL_Color incolor, std::string inname) {
		score = 0;
		color = incolor;
		name = inname;
	}
};

class Score_system
{
private:
	std::vector<Player> players;
	int score_to_add;
	void add_score(SDL_Color color);
	void add_player(SDL_Color incolor, std::string inname);
public:
	Score_system();
};

