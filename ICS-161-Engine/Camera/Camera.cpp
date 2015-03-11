#include "Camera.h"
#include <iostream>

Camera::Camera(SDL_Renderer* renderer, SDL_Rect rect){
	this->camera = rect;
	this->renderer = renderer;
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
	return camera.x;
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

//scrolls through a level by x
//@param incr how many pixels to move each call
//@param levelW width of the level
//@param screenW width of the screen
void Camera::scrollX(int incr, int levelW){
	if (camera.x < levelW - camera.w){
		camera.x += incr;
	}
}
//scrolls through a level by y
//@param incr how many pixels to move each call
//@param levelH height of the level
//@param screenH height of the screen
void Camera::scrollY(int incr, int levelH){
	if (camera.y < levelH - camera.h){
		camera.y += incr;
	}
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

void Camera::render(int x, int y, SDL_Texture* texture){
	//set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, camera.w, camera.h };

	//set clip rendering dimensions
	if (&camera != NULL){
		renderQuad.w = camera.w;
		renderQuad.h = camera.h;
	}

	//render to screen
	SDL_RenderCopy(renderer, texture, &camera, &renderQuad);
}
