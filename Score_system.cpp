#include "Score_system.h"


Score_system::Score_system() {
	score_to_add = 0;
}

void Score_system::add_score(SDL_Color color) {
	for (auto it = players.begin(); it != players.end(); it++) {
		if (it->color.r == color.r && it->color.g == color.g && it->color.b == color.b) {
			it->score += score_to_add;
			score_to_add++;
			return;
		}
	}
	return;
}


void Score_system::add_player(SDL_Color incolor, std::string inname, int left, int right) {
	players.push_back({ incolor, inname ,left, right});
	return;
}


void Score_system::init_round(SDL_Renderer* renderer) {
	score_to_add = 0;
	render_scores(renderer);
}


void Score_system::render_scores(SDL_Renderer* renderer) {
	double size = players.size();
	render_score_rect(renderer, {255, 255, 255, 255}, 1220, 195, 1580, 200);
	for (int i = 0; i < players.size(); i++) {
		if (players[i].score == 0) {
			continue;
		}
		int posx = 1200 + ((1 / size) * 400 * i) + (1 / size) * 400 * 0.2;
		int posy = 200 + 500 * (1 - (double(players[i].score) / ((size - 1) * 10)));
		int width = int((1 / size) * 400 * 0.6);
		int height = 500 * (double(players[i].score) / ((size - 1) * 10));
		int posx2 = posx + width;
		int posy2 = posy + height;
		render_score_rect(renderer, players[i].color, posx, posy, posx2, posy2);
	}
}


void Score_system::render_score_rect(SDL_Renderer* renderer, SDL_Color color, int x, int y, int x2, int y2) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = x; i <= x2; i++) {
		SDL_RenderDrawLine(renderer, i, y, i, y2);
	}
}

