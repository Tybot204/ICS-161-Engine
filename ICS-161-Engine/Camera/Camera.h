#pragma once
#include "SDL.h"
#include "../Sprite/Sprite.h"



class Camera{
public:
	Camera(SDL_Renderer* renderer, int x, int y, int w, int h);
	~Camera();

	//return camera dimensions;
	int getWidth();
	int getHeight();
	int getX();
	int getY();

	//moves the camera by x and y units
	void move(int xdelta, int ydelta);

	//sets the position of the camera by x and y units
	void setPos(int x, int y);

	//render texture at given point
	void render(int x, int y, Sprite* sprite, std::string sequence);

	//center camera over some object and keep from going outside the level
	void fixCameraPosition(int levelwidth, int levelheight);

private:
	SDL_Renderer* renderer;
	SDL_Rect camera;

};