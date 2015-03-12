#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
	this->renderer = renderer;
}

Game::~Game() {}

void Game::start() {
	const std::string resPath = "assets\\";
	SDL_Texture* background = IMG_LoadTexture(renderer, (resPath + "res/land.png").c_str());
	//Sprite* spriteBG = new Sprite(0, 0, resPath + "bg.txt", renderer);
	Sprite* fire = new Sprite(250, 250, resPath + "fire.txt", renderer);
	Sprite* health = new Sprite(0, 0, resPath + "number.txt", renderer);
	Camera* camera = new Camera(renderer, SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	player->attachCamera(camera);
	fire->setAX(proj_accelX);
	int col_code = 0;
	int score = 9;
	std::stringstream ss;
	ss << score;
	std::string num = ss.str();
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					player->move(0, -5);
					break;
				case SDLK_d:
					player->move(5, 0);
					break;
				case SDLK_s:
					player->move(0, 5);
					break;
				case SDLK_a:
					player->move(-5, 0);
					break;
				}
			}
		}
		
		col_code = checkBounds(fire->getX(), fire->getY(), SCREEN_WIDTH, SCREEN_HEIGHT);
		if (col_code == 1)
		{
			//std::cout << "Bounds : " << col_code << std::endl;
			fire->setVX(reflectfront[0]);
			fire->setVY(reflectfront[1]);
			fire->setAX(reflectfront[2]);
		}
		else if (col_code == 2)
		{
			//std::cout << "Bounds : " << col_code << std::endl;
			fire->setVX(reflectback[0]);
			fire->setVY(reflectback[1]);
			fire->setAX(reflectback[2]);
		}

		else if (col_code == 3)
		{
			//std::cout << "Bounds : " << col_code << std::endl;
			fire->setVY(reflecttop[0]);
			fire->setAX(reflecttop[1]);
			fire->setAY(reflecttop[2]);
		}

		else if (col_code == 4)
		{
			//std::cout << "Bounds : " << col_code << std::endl;
			fire->setVY(fire->getVY()*-1);
			fire->setAY(reflectfront[2]);
		}

		if (collide(*player->returnSprite(), *fire))
		{
			//std::cout << "Collided!" << std::endl;
			fire->setVY(fire->getVY()*-2);
			fire->setVX(fire->getVX()*-2);
			if (score > 0)
			{
				score--;
			}

		}
		fire->update();
		std::stringstream ss;
		ss << score;
		std::string num = ss.str();
		//Render the scene
		if (renderer != nullptr) {
			SDL_RenderClear(renderer);
			camera->render(0, 0, background);
			fire->show("fire", 1);
			health->show(num, 0);
			//spriteBG->show("background", 1);
			currentLevel->on_screen_check(camera);
			currentLevel->render_on_screen(camera);
			camera->fixCameraPosition(LEVEL_WIDTH, LEVEL_HEIGHT);
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

	std::cout << "JSON File Contents:" << std::endl;
	std::cout << "Player" << std::endl;
	std::cout << "    filename: " << root["player"]["filename"].asString() << std::endl;
	std::cout << "    currX: " << root["player"]["currX"].asDouble() << std::endl;
	std::cout << "    currY: " << root["player"]["currY"].asDouble() << std::endl;
	std::cout << "    sequence: " << root["player"]["sequence"].asString() << std::endl;
	for (int i = 0; i < root["sprites"].size(); i++) {
		std::cout << "Sprite-" << i << std::endl;
		std::cout << "    filename: " << root["sprites"][i]["filename"].asString() << std::endl;
		std::cout << "    currX: " << root["sprites"][i]["currX"].asDouble() << std::endl;
		std::cout << "    currY: " << root["sprites"][i]["currY"].asDouble() << std::endl;
		std::cout << "    sequence: " << root["sprites"][i]["sequence"].asString() << std::endl;
	}

	std::vector<std::pair<Sprite*, Sequence>> sprites = {};
	for (int i = 0; i < root["sprites"].size(); i++) {
		Sprite* sprite = new Sprite(root["sprites"][i]["currX"].asDouble(), root["sprites"][i]["currY"].asDouble(), "assets\\" + root["sprites"][i]["filename"].asString(), renderer);
		Sequence sequence = std::make_pair(root["sprites"][i]["sequence"].asString(), root["sprites"][i]["sequence"].asString());
		sprites.push_back(std::make_pair(sprite, sequence));
	}

	player = new Player(new Sprite(root["player"]["currX"].asDouble(), root["player"]["currY"].asDouble(), "assets\\" + root["player"]["filename"].asString(), renderer));
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
