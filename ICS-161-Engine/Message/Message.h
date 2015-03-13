//Message.h
#pragma once

//Header files

#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"
#include "../Player/Player.h"


class Message{

public:
	Message(Camera* camera);
	Message(Sprite* sprite);
	Message(Player* player, std::string messageStr);
	Message();
	~Message();

	void execute();
	Camera* AccessCamera();
	Sprite* AccessSprite();
	Player* AccessPlayer();
	std::string messageType();

private:
	Camera* camera;
	Sprite* sprite;
	Player* player;
	std::string messageStr;
};
