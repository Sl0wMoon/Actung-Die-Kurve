#include "Snake.h"



Snake::Snake(int heading, int xposition, int yposition, SDL_Color snake_color, int left, int right) {
    alive = true;
	Snake::heading = heading;
	position.x = xposition;
	position.y = yposition;
    previous_position.x = xposition;
    previous_position.y = yposition;
	amplitude = 1.5;
	speed.x = std::cos(degreetorad(heading)) * amplitude;
	speed.y = std::sin(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
	size = 3;
    Snake::snake_color = snake_color;
    trail_color = snake_color;
    head_color = { 255, 255, 0 };
    right_key = right;
    left_key = left;
}


Snake::Snake() {
    alive = true;
	heading = 0;
	size = 3;
	position.x = 800;
	position.y = 450;
    previous_position.x = 800;
    previous_position.y = 450;
	amplitude = 3;
	speed.x = std::cos(degreetorad(heading)) * amplitude;
	speed.y = std::sin(degreetorad(heading)) * amplitude;
	steer_amount = 0;
	steer_multiplier = 1;
    snake_color = { 255, 255, 255 };
    trail_color = snake_color;
    head_color = { 255, 255, 0 };
    right_key = 79;
    left_key = 80;
}


void Snake::steer() {
	heading += steer_amount;
    speed.x = std::cos(degreetorad(heading)) * amplitude;
	speed.y = std::sin(degreetorad(heading)) * amplitude;
}


Twod Snake::make_heading_vect(int heading) {
    return Twod(std::cos(degreetorad(heading)), std::sin(degreetorad(heading)));
}


void Snake::turn_left() {
	steer_amount = -1 * steer_multiplier;
}


void Snake::turn_right() {
	steer_amount = 1 * steer_multiplier;
}


void Snake::turn_fwd() {
    steer_amount = 0;
}


void Snake::move() {
    previous_position = position;
	position.x += speed.x;
	position.y += speed.y;

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
    int x = round(point.x);
    int y = round(point.y);
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
    double rad = (degree * M_PI) / 180;
    return rad;
}


void Snake::draw_snake(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, trail_color.r, trail_color.g, trail_color.b, 255);
    draw_circle(renderer, previous_position);
    SDL_SetRenderDrawColor(renderer, head_color.r, head_color.g, head_color.b, 255);
    draw_circle(renderer, position);
}

void Snake::stop_draw(SDL_Renderer* renderer) {
    trail_color = { 0, 0, 0, 255 };
    Twod normal = { speed.y * size / amplitude , -speed.x * size / amplitude };
    SDL_Rect cutoff = { position.x + normal.x*2, position.y + normal.y*2, size * 4, size + amplitude + 3 };
    draw_rotated_rect(renderer, cutoff, heading);
}


void Snake::start_draw(SDL_Renderer* renderer) {
    trail_color = snake_color;
    draw_snake(renderer);
    Twod normal = { speed.y * size / amplitude , -speed.x * size / amplitude };
    SDL_Rect cutoff = { position.x + normal.x * 2 + speed.x * -2, position.y + normal.y * 2 + speed.y * -2, size * 3.75, size + amplitude + 10 };
    trail_color = { 0, 0, 0, 255 };
    draw_rotated_rect(renderer, cutoff, heading);
    trail_color = snake_color;
}


Twod Snake::get_pos() {
    return position;
}


void Snake::check_collision(SDL_Window* window, Uint32* pixel) {
    for (int i = -1; i <= 1; i ++) {
        int direction = 360 * i/6 + heading;
        float mult = 1.5f;
        Twod check_vect = { std::cos(degreetorad(direction)) * (size * mult) , std::sin(degreetorad(direction)) * (size * mult)};
        auto renderer = SDL_GetRenderer(window);
        SDL_Color color = find_color(window, { position.x + check_vect.x , position.y + check_vect.y }, pixel);
        if (color.r != 0 || color.g != 0 || color.b != 0) {
            alive = false;
            return;
        }
        /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, position.x + check_vect.x, position.y + check_vect.y);*/

    }
}



SDL_Color Snake::find_color(SDL_Window* window, Twod pos, Uint32* pixel) {
    SDL_Color color = { 0, 0, 0, 255 };
    int offset = int(pos.x) + int(pos.y) * 1600;
    SDL_GetRGB(pixel[offset], SDL_GetWindowSurface(window)->format, &color.r, &color.g, &color.b);
    return color;
}


const bool Snake::is_alive() {
    return alive;
}


void Snake::handle_input(SDL_Renderer* renderer) {
    auto keystates = SDL_GetKeyboardState(NULL);

    if (keystates[left_key] && !(get_turn() < 0)) {
        turn_left();
    }
    if (keystates[right_key] && !(get_turn() > 0)) {
        turn_right();
    }
    if (keystates[right_key] + keystates[left_key] == 0 && get_turn() != 0) {
        turn_fwd();
    }
    if (keystates[SDL_SCANCODE_BACKSPACE]) {
        stop_draw(renderer);
    }
    if (keystates[SDL_SCANCODE_TAB]) {
        start_draw(renderer);
    }
}


void Snake::draw_rotated_rect(SDL_Renderer* renderer, SDL_Rect rect, double angle) {
    SDL_Surface* filledSurface = SDL_CreateRGBSurface(0, 100, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(filledSurface, nullptr, SDL_MapRGB(filledSurface->format, trail_color.r, trail_color.g, trail_color.b));
    SDL_Texture* filledTexture = SDL_CreateTextureFromSurface(renderer, filledSurface);
    SDL_FreeSurface(filledSurface);

    SDL_Rect dstRect = rect;
    angle += 90;
    // Set the rotation point relative to the top-left corner
    SDL_Point rotationPoint = { 0, 0 };

    // Render the filled rotated rectangle
    SDL_RenderCopyEx(renderer, filledTexture, nullptr, &dstRect, angle, &rotationPoint, SDL_FLIP_NONE);
}


void Snake::handle_stop_draw(SDL_Renderer* renderer, int tick) {
    int modnum = tick % 300;
    if (modnum == 270) {
        stop_draw(renderer);
        return;
    }
    if (modnum == 0) {
        start_draw(renderer);
        return;
    }
    return;
}