#include "Snake.h"



Snake::Snake(int heading, int xposition, int yposition) {
	Snake::heading = heading;
	position.x = xposition;
	position.y = yposition;
	amplitude = 2;
	speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
	size = 5;
    anchor = Twod(position.x, position.y);
}


Snake::Snake() {
	heading = 0;
	size = 5;
	position.x = 800;
	position.y = 450;
	amplitude = 2;
	speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
    anchor = Twod(800, 450);
}


void Snake::steer() {
	heading += steer_amount;
    speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
}


void Snake::turnleft() {
    if (get_turn() <= 0) {
        add_to_tail();
    }
	steer_amount = 1 * steer_multiplier;
}


void Snake::turnright() {
    if (get_turn() >= 0) {
        add_to_tail();
    }
	steer_amount = -1 * steer_multiplier;
}


void Snake::move() {
	position.x += speed.x;
	position.y += speed.y;
}


void Snake::turnfwd() {
    if (get_turn() != 0) {
        add_to_tail();
    }
    steer_amount = 0;
}


int Snake::get_turn() {
	if (steer_amount > 0)
		return 1;
	else if (steer_amount < 0)
		return -1;
	return 0;
}


int Snake::draw_head(SDL_Renderer* renderer){
    int offsetx, offsety, d;
    int status;
    int x = position.x;
    int y = position.y;
    int radius = size;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


double Snake::degreetorad(int degree) {
    double rad = (degree * 3.14159) / 180;
    return rad;
}


void Snake::draw_tail(SDL_Renderer* renderer) {
    for (auto it = trail.begin(); it != trail.end(); it++) {
        int direct = (it->direction + 180) % 360;
        int str = -it->steer;
        Twod current_pos = it->b;
        Twod movement_vect = Twod(std::sin(degreetorad(direct)) * it->spd, std::cos(degreetorad(direct)) * it->spd);
        while ((current_pos.x - it->a.x) * (current_pos.x - it->a.x) + (current_pos.y - it->a.y) * (current_pos.y - it->a.y) > 1) {
            draw_tail_part(renderer, current_pos.x, current_pos.y);
            movement_vect = Twod(std::sin(degreetorad(direct)) * it->spd, std::cos(degreetorad(direct)) * it->spd);
            current_pos.x += movement_vect.x;
            current_pos.y += movement_vect.y;
            direct += str;
        }
    }
}


void Snake::draw_snake(SDL_Renderer* renderer) {
    draw_head(renderer);
    draw_tail(renderer);
}


Twod Snake::get_pos() {
    return position;
}


void Snake::add_to_tail() {
    trail.push_back(Curve(anchor, position, amplitude, heading, steer_amount));
    anchor = position;
}


int Snake::draw_tail_part(SDL_Renderer* renderer, int posx, int posy) {
    int offsetx, offsety, d;
    int status;
    int x = posx;
    int y = posy;
    int radius = size;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}