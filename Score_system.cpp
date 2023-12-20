#include "Score_system.h"


Score_system::Score_system() {
	score_to_add = 0;
}

void Score_system::add_score(SDL_Color color) {
	for (auto it = players.begin(); it != players.end(); it++) {
		if (it->color.r == color.r && it->color.g == color.g && it->color.b == color.b) {
			it->score += score_to_add;
			return;
		}
	}
	return;
}


void Score_system::add_player(SDL_Color incolor, std::string inname) {
	players.push_back({ incolor, inname });
	return;
}
