#include "Camera.h"
#include <iostream>

Camera::Camera(SDL_Rect rect){
	this->camera = rect;
}

Camera::~Camera(){};




//returns dimensions of screen;
int Camera::getWidth(){
	return camera.w;
}
int Camera::getHeight(){
	return camera.h;
}
int Camera::getX(){
	return camera.x;
}
int Camera::getY(){
	return camera.y;
}

//sets coordinates of camera at x and y
//@param x an int
//@param y an int
void Camera::setPos(int x, int y){
	camera.x = x;
	camera.y = y;
}

//center camera over some object and keep from going outside the level
void Camera::fixCameraPosition(int levelwidth, int levelheight){
	if (camera.x < 0){
		camera.x = 0;
	}
	if (camera.y < 0){
		camera.y = 0;
	}
	if (camera.x > levelwidth - camera.w){
		camera.x = levelwidth - camera.w;
	}
	if (camera.y > levelheight - camera.h){
		camera.y = levelheight - camera.y;
	}
}