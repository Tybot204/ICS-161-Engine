// SDL and c++ include files
#include <SDL.h>
#include "SDL_image.h"
#include <Windows.h>
#include "cleanup.h"

// Custom engine include files
#include "Game/Game.h"

int main(int argc, char **argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "IMG_Init" << " error: " << SDL_GetError() << std::endl;
		std::ostringstream errMsg;
		errMsg << " error: " << SDL_GetError() << std::endl;
		OutputDebugString(errMsg.str().c_str());
		SDL_Quit();
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("ICS 161 Game Engine", 800, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Game game = Game(window, renderer);
	game.start();
	cleanup(window, renderer);

	return 0;
}
