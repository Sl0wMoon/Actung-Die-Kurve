#include "Snake.h"



Snake::Snake(int heading, int xposition, int yposition) {
    alive = true;
	Snake::heading = heading;
	position.x = xposition;
	position.y = yposition;
    previous_position.x = xposition;
    previous_position.y = yposition;
	amplitude = 1.5;
	speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
	size = 3;
    color = { 255, 0, 0 };
    head_color = { 255, 255, 0 };
    right_key = 79;
    left_key = 80;
    //anchor = Twod(position.x, position.y);
}


Snake::Snake() {
    alive = true;
	heading = 0;
	size = 3;
	position.x = 800;
	position.y = 450;
    previous_position.x = 800;
    previous_position.y = 450;
	amplitude = 1.5;
	speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
    color = { 255, 0, 0 };
    head_color = { 255, 255, 0 };
    right_key = 79;
    left_key = 80;
    //anchor = Twod(800, 450);
}


void Snake::steer() {
	heading += steer_amount;
    speed.x = std::sin(degreetorad(heading)) * amplitude;
	speed.y = std::cos(degreetorad(heading)) * amplitude;
}


void Snake::turn_left() {
    /*if (get_turn() <= 0) {
        add_to_tail();
    }*/
	steer_amount = 1 * steer_multiplier;
}


void Snake::turn_right() {
    /*if (get_turn() >= 0) {
        add_to_tail();
    }*/
	steer_amount = -1 * steer_multiplier;
}


void Snake::move() {
    previous_position = position;
	position.x += speed.x;
	position.y += speed.y;
}


void Snake::turn_fwd() {
    /*if (get_turn() != 0) {
        add_to_tail();
    }*/
    steer_amount = 0;
}


int Snake::get_turn() {
	if (steer_amount > 0)
		return 1;
	else if (steer_amount < 0)
		return -1;
	return 0;
}


int Snake::draw_circle(SDL_Renderer* renderer, Twod point){
    int offsetx, offsety, d;
    int status;
    int x = point.x;
    int y = point.y;
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
    double rad = (degree * 3.141592653) / 180;
    return rad;
}


//void Snake::draw_tail(SDL_Renderer* renderer) {
//    for (auto it = trail.begin(); it != trail.end(); it++) {
//        int direct = (it->direction + 180) % 360;
//        int str = -it->steer;
//        Twod current_pos = it->b;
//        Twod movement_vect = Twod(std::sin(degreetorad(direct)) * it->spd, std::cos(degreetorad(direct)) * it->spd);
//        while ((current_pos.x - it->a.x) * (current_pos.x - it->a.x) + (current_pos.y - it->a.y) * (current_pos.y - it->a.y) > 1) {
//            draw_tail_part(renderer, current_pos.x, current_pos.y);
//            movement_vect = Twod(std::sin(degreetorad(direct)) * it->spd, std::cos(degreetorad(direct)) * it->spd);
//            current_pos.x += movement_vect.x;
//            current_pos.y += movement_vect.y;
//            direct += str;
//        }
//    }
//}


void Snake::draw_snake(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    draw_circle(renderer, previous_position);
    SDL_SetRenderDrawColor(renderer, head_color.r, head_color.g, head_color.b, 255);
    draw_circle(renderer, position);
    //draw_tail(renderer);
}


Twod Snake::get_pos() {
    return position;
}


//void Snake::add_to_tail() {
//    trail.push_back(Curve(anchor, position, amplitude, heading, steer_amount));
//    anchor = position;
//}


//int Snake::draw_tail_part(SDL_Renderer* renderer, int posx, int posy) {
//    int offsetx, offsety, d;
//    int status;
//    int x = posx;
//    int y = posy;
//    int radius = size;
//
//    offsetx = 0;
//    offsety = radius;
//    d = radius - 1;
//    status = 0;
//
//    while (offsety >= offsetx) {
//
//        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
//            x + offsety, y + offsetx);
//        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
//            x + offsetx, y + offsety);
//        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
//            x + offsetx, y - offsety);
//        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
//            x + offsety, y - offsetx);
//
//        if (status < 0) {
//            status = -1;
//            break;
//        }
//
//        if (d >= 2 * offsetx) {
//            d -= 2 * offsetx + 1;
//            offsetx += 1;
//        }
//        else if (d < 2 * (radius - offsety)) {
//            d += 2 * offsety - 1;
//            offsety -= 1;
//        }
//        else {
//            d += 2 * (offsety - offsetx - 1);
//            offsety -= 1;
//            offsetx += 1;
//        }
//    }
//
//    return status;
//}


void Snake::check_collision(SDL_Window* window) {
    for (int i = -1; i <= 1; i++) {
        int direction = 360 * i/5 + heading;
        Twod check_vect = { std::sin(degreetorad(direction)) * (size + 0.8) , std::cos(degreetorad(direction)) * (size + 0.8)};
        auto renderer = SDL_GetRenderer(window);
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDrawPoint(renderer, position.x + check_vect.x, position.y + check_vect.y);
        SDL_Color color = find_color(window, { position.x + check_vect.x , position.y + check_vect.y });
        if (color.r != 0 || color.g != 0 || color.b != 0) {
            alive = false;
            return;
        }
    }
}



SDL_Color Snake::find_color(SDL_Window* window, Twod pos) {
    Uint32* pixel = new Uint32;   
    SDL_Color color = { -1, -1, -1, -1 };

    auto renderer = SDL_GetRenderer(window);
    auto surface = SDL_GetWindowSurface(window);
    auto src = SDL_Rect({ int(pos.x), int(pos.y) , 1, 1 });
    SDL_RenderReadPixels(renderer, &src, SDL_PIXELFORMAT_RGB888, pixel, surface->format->BytesPerPixel);
    SDL_GetRGB(*pixel, surface->format, &color.r,  &color.g, &color.b);
    return color;
}


const bool Snake::is_alive() {
    if (alive)
        return true;
    return false;
}


void Snake::handle_input() {
    auto keystates = SDL_GetKeyboardState(NULL);

    if (keystates[left_key] && !(get_turn() == 1)) {
        turn_left();
    }
    if (keystates[right_key] && !(get_turn() == -1)) {
        turn_right();
    }
    if (keystates[right_key] + keystates[left_key] == 0) {
        turn_fwd();
    }
}