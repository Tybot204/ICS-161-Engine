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

void Player::move() {

}

void Player::show() {
	sprite->show("run right", 0);
}
