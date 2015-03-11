#include "Player.h"

Player::Player(Sprite* sprite, Camera* camera) {
	this->sprite = sprite;
	this->camera = camera;
}

Player::~Player() {
	delete sprite;
	delete camera;
}

void Player::move() {

}
