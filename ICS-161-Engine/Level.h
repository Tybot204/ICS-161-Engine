#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "Json/json.h"
#include "Sprite\Sprite.h"

class Level{
public:
	Level(SDL_Renderer* renderer, std::vector<std::pair<Sprite*, Sequence>> offScreenSprites);
	~Level();

	//render images in camera frustrum
	void on_screen_check(int camera_x_pos, int camera_y_pos, int camera_height, int camera_width);
	void render_on_screen();

private:
	SDL_Renderer* renderer_;
	std::vector<std::pair<Sprite*, Sequence>> onScreenSprites_;
	std::vector<std::pair<Sprite*, Sequence>> offScreenSprites_;
};