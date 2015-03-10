#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
	this->renderer = renderer;
}

Game::~Game() {}

void Game::start() {
	const std::string resPath = "assets\\";
	SDL_Texture* background = IMG_LoadTexture(renderer, (resPath + "res/Background.png").c_str());

	Camera camera = Camera(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					camera.move(0, -5);
					break;
				case SDLK_d:
					camera.move(5, 0);
					break;
				case SDLK_s:
					camera.move(0, 5);
					break;
				case SDLK_a:
					camera.move(-5, 0);
					break;
				}
			}
		}

		//Render the scene
		if (renderer != nullptr) {
			SDL_RenderClear(renderer);
			SDL_Rect dst = { 0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };
			SDL_RenderCopy(renderer, background, NULL, &dst);
			SDL_RenderPresent(renderer);
		}
		else {
			std::cout << "No renderer created" << std::endl;
			break;
		}
	}
	if (!save()) {
		std::cout << "Unable to save level" << std::endl;
	}
	IMG_Quit();
	SDL_Quit();
}

bool Game::load(std::string filename) {
	std::ifstream ifs(filename);
	std::string json((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	Json::Value root;
	Json::Reader reader;
	bool parsed = reader.parse(json.c_str(), root, false);
	if (!parsed) {
		std::cout << "Failed to load level" << std::endl;
		return false;
	}
	currentLevel = root;
	return true;
}

bool Game::save() {
	return true;
}

void Game::setWindow(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
	this->renderer = renderer;
}
