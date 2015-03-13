#include "Message.h"

//Message.cpp

Message::Message(Camera* camera)
{
	this->camera = camera;
}

Message::Message(Sprite* sprite)
{
	this->sprite = sprite;
}

Message::Message(Player* player, std::string messageStr)
{
	this->player = player;
	this->messageStr = messageStr;
}


Message::Message() {}

Message::~Message()
{
	delete camera;
	delete sprite;
	delete player;
}

void Message::execute()
{
	//Move Up Case
	if (messageStr == "Up Movement")
	{
		player->move(0, -5);
		std::cout << "Up Movement" << std::endl;
	}

	//Move Right Case
	else if (messageStr == "Right Movement")
	{
		player->move(5, 0);
		std::cout << "Right Movement" << std::endl;
	}

	//Move Down Case
	else if (messageStr == "Down Movement")
	{
		player->move(0, 5);
		std::cout << "Down Movement" << std::endl;
	}

	//Move Left Case
	else if (messageStr == "Left Movement")
	{
		player->move(-5, 0);
		std::cout << "Left Movement" << std::endl;
	}

	//Extra Cases
	//Jump Case
	else if (messageStr == "Jump")
	{
		player->move(0, 15);
	}

	else if (messageStr == "Fire")
	{
		//Shoot projectile and adjust sprite accordingly

		//std::cout << "Fire" << std::endl;
	}

	else if (messageStr == "Duck")
	{
		//adjust sprite to duck

		//std::cout << "Duck" << std::endl;
	}

	else if (messageStr == "Sprint")
	{
		//adjust movement speed (increase speed by 5) 

		//std::cout << "Sprinting" << std::endl;
	}
}

Camera* Message::AccessCamera()
{
	return this->camera;
}

Sprite* Message::AccessSprite()
{
	return this->player->returnSprite();
}

Player* Message::AccessPlayer()
{
	return this->player;
}

std::string Message::messageType()
{
	return this->messageStr;
}



