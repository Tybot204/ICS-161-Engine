#pragma once

//SDL and c++ include files
#include <string>
#include <fstream>
#include <vector>
#include "SDL.h"

//Custom engine include files
#include "../Sprite/Sprite.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"

class Level{
public:
	Level(Player* player, std::vector<std::pair<Sprite*, Sequence>> sprites, int level_width, int level_height);
	~Level();

	//render images in camera frustrum
	void on_screen_check(Camera* camera);
	void render_on_screen(Camera* camera);
	int get_level_width();
	int get_level_height();
	std::vector<Sprite*> get_all_sprites();

private:
	std::vector<std::pair<Sprite*, Sequence>> onScreenSprites_;
	std::vector<std::pair<Sprite*, Sequence>> offScreenSprites_;
	int level_width_;
	int level_height_;
	Player* player_;
};
