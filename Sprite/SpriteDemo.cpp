#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "Sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//const std::string resPath = getResourcePath("SpriteDemo");
	const std::string resPath = "Demo\\";
	// background is from "iceland1.jpg" at theadventurousmailbox.com
	//SDL_Texture *background = loadTexture(resPath + "Untitled.png", renderer);
	//Make sure all is well
	//if (background == nullptr){
	//	cleanup(background, renderer, window);
	//	IMG_Quit();
	//	SDL_Quit();
	//	return 1;
	//}

	Sprite* spriteBG = new Sprite(resPath + "Document1.txt", renderer);
	spriteBG->setPos(0, 0);
	//int bgFrame = spriteBG->makeFrame(background, 0, 0);

	//SDL_Texture *spritesheet = loadTexture(resPath + "y01uPOi.png", renderer);
	// spritesheet is from "y01uPOi.png" at http://forums.rpgmakerweb.com/index.php?/topic/19159-when-making-sprite-sheets-how-does-rpg-know-which-one-to-start-with/
	//if (spritesheet == nullptr){
	//	cleanup(spritesheet, renderer, window);
	//	IMG_Quit();
	//	SDL_Quit();
	//	return 1;
	//}

	Sprite* sprite1 = new Sprite(resPath + "Document2.txt", renderer);
	//for (int i = 0; i < 9; ++i)
	//{
	//	for (int j = 0; j < 3; ++j)
	//	{
	//		sprite1->addFrameToSequence("walk up", sprite1->makeFrame(spritesheet, i * 32, 0));
	//		sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, i * 32, 64));
	//		sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, i * 32, 128));
	//		sprite1->addFrameToSequence("walk down", sprite1->makeFrame(spritesheet, i * 32, 192));
	//	}
	//}

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	sprite1->setPos(x, y);

	SDL_Event e;
	bool quit = false;
	std::string spriteDirection = "walk right";
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					sprite1->movex(1);
					spriteDirection = "walk right";
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					sprite1->movex(-1);
					spriteDirection = "walk left";
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					sprite1->movey(-1);
					spriteDirection = "walk up";
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					sprite1->movey(1);
					spriteDirection = "walk down";
				}
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		spriteBG->show("background");
		sprite1->show(spriteDirection);
		SDL_RenderPresent(renderer);
	}

	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();

	SDL_Quit();

	return 0;
}
