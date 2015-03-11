#include "Player.h"

Player::Player(Sprite* sprite) {
	this->sprite = sprite;
}

Player::~Player() {
	delete sprite;
	delete camera;
}

void Player::attachCamera(Camera* camera) {
	this->camera = camera;
}

void Player::move(int deltaX, int deltaY) {
	camera->move(deltaX, deltaY);
	sprite->movex(deltaX);
	sprite->movey(deltaY);
}

void Player::show() {
	sprite->show("run right", 1);
}
