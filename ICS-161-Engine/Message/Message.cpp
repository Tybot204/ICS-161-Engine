#include "Message.h"

//Message.cpp

Message::Message(Camera camera, int message)
{
	camera = camera;
	message_type = message;
}

Message::Message(Sprite sprite, int message)
{
	sprite = sprite;
	message_type = message;
}

Message::Message() {}
Message::~Message(){}

void Message::move()
{
	//UP Case
	if (message_type == 1)
	{
		camera.move(0, -5);
	}

	//Right Case
	else if (message_type == 2)
	{
		camera.move(5, 0);
	}

	//Down Case
	else if (message_type == 3)
	{
		camera.move(0, 5);
	}

	//Left Case
	else if (message_type == 4)
	{
		camera.move(-5, 0);
	}

	//Extra cases
}
