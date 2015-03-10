#pragma once

#include <SDL.h>
#include "../Sprite/Sprite.h"

class Camera{
public:
	Camera(SDL_Rect rect);
	~Camera();

	//return camera dimensions;
	int getWidth();
	int getHeight();
	int getX();
	int getY();

	//scrolls through a level by the x axis
	void scrollX(int incr, int levelW, int screenW);
	//scrolls through a level by the y axis
	void scrollY(int incr, int levelH, int screenH);

	//sets coordinates of camera at x and y
	void setPos(int x, int y);


	//keeps from going outside the level
	void fixCameraPosition(int levelwidth, int levelheight);

private:
	SDL_Rect camera;
};
