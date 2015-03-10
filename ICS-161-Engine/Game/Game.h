#pragma once

// SDL and c++ header files
#include <iostream>
#include <sstream>
#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <fstream>

// Custom engine header files
#include "../Sprite/Sprite.h"
#include "../Json/json.h"
#include "../Camera/Camera.h"
#include "../Level/Level.h"

// Engine-wide constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// Temporary constants, should be moved to the JSON file
const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 700;

class Game{
public:
	Game(SDL_Window* window, SDL_Renderer* renderer);
	~Game();

	void start();
	bool load(std::string filename);
	bool save();
	void logSDLError(std::ostream &os, const std::string &msg);
	void setWindow(SDL_Window* window, SDL_Renderer* renderer);

private:
	Level* currentLevel;
	SDL_Renderer* renderer;
	SDL_Window* window;

};
