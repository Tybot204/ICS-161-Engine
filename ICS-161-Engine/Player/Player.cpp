#include "Player.h"

Player::Player(Sprite* sprite) {
	this->sprite = sprite;
	sequence = "stand right";
}

Player::~Player() {
	delete sprite;
	delete camera;
}

void Player::attachCamera(Camera* camera) {
	this->camera = camera;
}

void Player::move(int deltaX, int deltaY) {
	if (deltaX > 0) {
		sequence = "run right";
	}
	else if (deltaX < 0) {
		sequence = "run left";
	}
	else if (deltaY > 0) {
		sequence = "descend left";
	}
	else if (deltaY < 0) {
		sequence = "rise right";
	}
	camera->move(deltaX, deltaY);
	sprite->movex(deltaX);
	sprite->movey(deltaY);
}

void Player::show() {
	sprite->show(sequence, 1);
}

Sprite* Player::returnSprite()
{
	return(this->sprite);
}