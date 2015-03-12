#include "AudioManager.h"
#include <iostream>

AudioManager* AudioManager::instance;

AudioManager* AudioManager::getInstance()
{
	if (!instance)
		instance = new AudioManager();

	return instance;
}

AudioManager::~AudioManager()
{
	Mix_FreeMusic(music);

	for (std::map<std::string, Mix_Chunk*>::iterator it = soundMap.begin(); it != soundMap.end(); ++it)
	{
			Mix_FreeChunk((*it).second);
	}

}

void AudioManager::loadMusic(std::string songName)
{
	music = Mix_LoadMUS(songName.c_str());
	if (music == NULL)
		std::cout << "Music Not Loaded \n";
}

//sound is loaded into the buffer, if the filename is not found prints out, can be changed into a error later.
void AudioManager::loadSound(std::string soundName, std::string fileName)
{
	//create a new soundbuffer;
	Mix_Chunk* buffer = new Mix_Chunk;
	//load the file
	buffer = Mix_LoadWAV(fileName.c_str());
	if (buffer == NULL)
	{
		//insert into the map
		std::cout << "Sound Not Loaded \n";
	}

	soundMap.insert(std::pair<std::string, Mix_Chunk*>(soundName.c_str(), buffer));
}

//return the sound buffer
Mix_Chunk* AudioManager::getSound(std::string soundName)
{
	if (soundMap.at(soundName) == NULL)
	{
		std::cout << "Sound Not Loaded \n";
		return NULL;
	}
	else 
		return soundMap.at(soundName);

}

void AudioManager::playMusic()
{
	if (music == NULL)
	{
		std::cout << "Music Not Loaded \n";
	}
	else if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(music, -1);
	}
	else
	{
		std::cout << "Music Already Playing \n";
	}

}


void AudioManager::stopMusic()
{
	if (music == NULL)
		std::cout << "Music Not Loaded \n";
	else
		Mix_HaltMusic();
}
void AudioManager::setMusicVolume(float volume)
{
	if (music == NULL)
		std::cout << "Music Not Loaded \n";
	else
		Mix_VolumeMusic(volume);
}
void AudioManager::setMusicLoop(bool loop)
{
	if (music == NULL)
		std::cout << "Music Not Loaded \n";
	else
	{
		Mix_PauseMusic();
		if (loop)
			Mix_PlayMusic(music, -1);
		else
			Mix_PlayMusic(music, 0);
		Mix_ResumeMusic();
	}
}

void AudioManager::playSound(std::string soundName, int loop)
{
	if (soundMap.at(soundName) != NULL && !Mix_Playing(-1))
		Mix_PlayChannel(-1, soundMap.at(soundName), loop);
}

void AudioManager::setSoundVolume(std::string soundName, int volume)
{
	if (soundMap.at(soundName) == NULL)
		std::cout << "Sound Not Loaded \n";
	else
		Mix_VolumeChunk(soundMap.at(soundName), volume);
}