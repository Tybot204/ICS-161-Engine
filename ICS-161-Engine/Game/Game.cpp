#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
	this->renderer = renderer;
}

Game::~Game() {}

void Game::start() {
	const std::string resPath = "assets\\";
	SDL_Texture* background = IMG_LoadTexture(renderer, (resPath + "res/Background.png").c_str());

	Camera* camera = new Camera(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	player->attachCamera(camera);

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					camera->move(0, -5);
					break;
				case SDLK_d:
					camera->move(5, 0);
					break;
				case SDLK_s:
					camera->move(0, 5);
					break;
				case SDLK_a:
					camera->move(-5, 0);
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
	std::ifstream ifs("levels/" + filename);
	std::string json((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	Json::Value root;
	Json::Reader reader;
	bool parsed = reader.parse(json.c_str(), root, false);
	if (!parsed) {
		std::cout << "Failed to load level" << std::endl;
		return false;
	}

	std::vector<std::pair<Sprite*, Sequence>> sprites = {};
	for (int i = 0; i < root["sprites"].size(); i++){
		Sprite* sprite = new Sprite(root["sprites"][i]["currX"].asDouble(), root["sprites"][i]["currY"].asDouble(), root["sprites"][i]["filename"].asString(), renderer);
		Sequence sequence = std::make_pair(root["sprites"][i]["sequence"].asString(), root["sprites"][i]["sequence"].asString());
		sprites.push_back(std::make_pair(sprite, sequence));
	}

	player = new Player(new Sprite(root["player"][1]["currX"].asDouble(), root["player"][2]["currY"].asDouble(), root["player"][0]["filename"].asString(), renderer));
	currentLevel = new Level(player, sprites, root["levelWidth"].asInt(), root["levelHeight"].asInt());

	return true;
}

bool Game::save() {
	return true;
}

void Game::setWindow(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
	this->renderer = renderer;
}
