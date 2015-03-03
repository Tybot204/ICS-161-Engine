#include "Camera.h"
#include <iostream>

Camera::Camera(SDL_Renderer* renderer, int x, int y, int w, int h){
	this->renderer = renderer;
	this->camera = { x, y, w, h };

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

//moves camera by x and y units
//@param xdelta an int
//@param ydelta an int
void Camera::move(int xdelta, int ydelta){
	camera.x += xdelta;
	camera.y += ydelta;
}

//sets coordinates of camera at x and y
//@param x an int
//@param y an int
void Camera::setPos(int x, int y){
	camera.x = x;
	camera.y = y;
}

//render texture at a given point
void Camera::render(int x, int y, Sprite* sprite, std::string sequence){
	//set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, camera.w, camera.h };

	//set clip rendering dimensions
	if (&camera != NULL){
		renderQuad.w = camera.w;
		renderQuad.h = camera.h;
	}

	//render to screen
	sprite->show(sequence, 0);
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