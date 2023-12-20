#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>


struct Player {
	std::string name;
	int score;
	SDL_Color color;
	int left_key;
	int right_key;
	Player() {
		name = "unnamed";
		score = 0;
		color = { 255, 255, 255, 255 };
		left_key = 80;
		right_key = 79;
	}
	Player(SDL_Color incolor, std::string inname, int left, int right) {
		score = 0;
		color = incolor;
		name = inname;
		left_key = left;
		right_key = right;
	}
};

class Score_system
{
private:
	std::vector<Player> players;
	int score_to_add;
public:
	Score_system();
	void init_round();
	void add_player(SDL_Color incolor, std::string inname, int left, int right);
	void add_score(SDL_Color color);
	inline std::vector<Player> get_players() { return players; }
};

