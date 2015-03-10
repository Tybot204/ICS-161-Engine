#include "Level.h"
#include <iostream>

Level::Level(SDL_Renderer* renderer, std::vector<std::pair<Sprite*, Sequence>> offScreenSprites)
{
	renderer_ = renderer;
	offScreenSprites_ = offScreenSprites;
}

void Level::on_screen_check(int camera_x_pos, int camera_y_pos, int camera_height, int camera_width)
{
	//check if off screen sprites enter the camera view
	//camera_height = y max
	//camera_width = x max
	//camera_width - camera_x_pos = x min
	//camera_height = camera_y_pos = y min
	bool flag;
	for (int i = 0; i < offScreenSprites_.size(); i++)
	{
		flag = false;
		if (offScreenSprites_[i].first->getBoundary().w + offScreenSprites_[i].first->getBoundary().x < camera_width + camera_x_pos)
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().h + offScreenSprites_[i].first->getBoundary().y < camera_height + camera_y_pos)
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().x - offScreenSprites_[i].first->getBoundary().w > camera_x_pos - camera_width)
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().y - offScreenSprites_[i].first->getBoundary().h > camera_y_pos - camera_height)
		{
			flag = true;
		}
		if (flag == true)
		{
			onScreenSprites_.push_back(offScreenSprites_[i]);
		}
	}
}

void Level::render_on_screen()
{
	for (int i = 0; i < onScreenSprites_.size(); i++)
	{
		
	}
}