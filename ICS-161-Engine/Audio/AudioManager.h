#pragma once
#pragma once

#include <string>
#include <vector>
#include <map>
#include <SDL_mixer.h>

class AudioManager
{

public:
	//call sound manager just like any other singlton
	static class AudioManager* getInstance();
	//load the main music from a file name, you can only have 1 main song playing
	void loadMusic(std::string songName);
	//load the sound effects from a file name and give it a key to find it by
	void loadSound(std::string soundName, std::string fileName);
	//returns a soundbuffer from the map based on its name
	Mix_Chunk* getSound(std::string soundName);
	//set volume for sound effects
	void setSoundVolume(std::string soundName, int volume);
	//set loop to -1 for infinite loop
	void playSound(std::string soundName, int loop);
	// play music set to loop by default
	void playMusic();
	void stopMusic();
	void setMusicVolume(float);
	void setMusicLoop(bool);
	Mix_Music *music;
private:                         
	~AudioManager();
	//map of sounds
	std::map < std::string, Mix_Chunk* > soundMap;
	std::vector<std::string> songList;
	static AudioManager* instance;
};