#include "Level.h"

Level::Level(Player* player, std::vector<std::pair<Sprite*, Sequence>> offScreenSprites, int level_width, int level_height)
{
	player_ = player;
	offScreenSprites_ = offScreenSprites;
	level_width_ = level_width;
	level_height_ = level_height;
}

void Level::on_screen_check(Camera* camera)
{
	//check if off screen sprites enter the camera view
	//camera height = y max
	//camera width = x max
	//camera width - camerax_pos = x min
	//camera height - cameray_pos = y min
	bool flag;
	for (int i = 0; i < offScreenSprites_.size(); i++)
	{
		flag = false;
		if (offScreenSprites_[i].first->getBoundary().w + offScreenSprites_[i].first->getBoundary().x < camera->getWidth() + camera->getX())
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().h + offScreenSprites_[i].first->getBoundary().y < camera->getHeight() + camera->getY())
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().x - offScreenSprites_[i].first->getBoundary().w > camera->getX() - camera->getWidth())
		{
			flag = true;
		}
		if (offScreenSprites_[i].first->getBoundary().y - offScreenSprites_[i].first->getBoundary().h > camera->getY() - camera->getHeight())
		{
			flag = true;
		}
		if (flag == true)
		{
			onScreenSprites_.push_back(offScreenSprites_[i]);
			offScreenSprites_.erase(offScreenSprites_.begin() + i);
		}
	}
}

void Level::render_on_screen(Camera* camera)
{
	bool flag;
	for (int i = 0; i < onScreenSprites_.size(); i++)
	{
		flag = false;
		if (onScreenSprites_[i].first->getBoundary().w + onScreenSprites_[i].first->getBoundary().x > camera->getWidth() + camera->getX() &&
			onScreenSprites_[i].first->getBoundary().h + onScreenSprites_[i].first->getBoundary().y > camera->getHeight() + camera->getY() &&
			onScreenSprites_[i].first->getBoundary().x - onScreenSprites_[i].first->getBoundary().w < camera->getX() - camera->getWidth() &&
			onScreenSprites_[i].first->getBoundary().y - onScreenSprites_[i].first->getBoundary().h < camera->getY() - camera->getHeight())
		{
			flag = true;
		}
		if (flag == true)
		{
			offScreenSprites_.push_back(onScreenSprites_[i]);
			onScreenSprites_.erase(onScreenSprites_.begin() + i);
		}
		else
		{
			onScreenSprites_[i].first->show(onScreenSprites_[i].second.first, 1);
		}
	}
	player_->show();
}

int Level::get_level_width()
{
	return level_width_;
}

int Level::get_level_height()
{
	return level_height_;
}

std::vector<Sprite*> Level::get_all_sprites() {
	std::vector<Sprite*> all_sprites;
	for (std::pair<Sprite*, Sequence> sprite_pair : onScreenSprites_) {
		all_sprites.push_back(sprite_pair.first);
	}
	for (std::pair<Sprite*, Sequence> sprite_pair : offScreenSprites_) {
		all_sprites.push_back(sprite_pair.first);
	}
	return all_sprites;
}
