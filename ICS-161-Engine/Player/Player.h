#pragma once

// SDL and c++ header files
#include <vector>

// Custom engine header files
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class Player{
public:
	Player(Sprite* sprite);
	~Player();

	void attachCamera(Camera* camera);
	void move(int deltaX, int deltaY);
	void show();

private:
	Sprite* sprite;
	Camera* camera;

};
