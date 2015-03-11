#pragma once

// SDL and c++ header files
#include <iostream>

// Custom engine header files
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class Player{
public:
	Player(Sprite* sprite, Camera* camera);
	~Player();

	void move();

private:
	Sprite* sprite;
	Camera* camera;

};
