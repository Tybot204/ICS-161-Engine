#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <map>

class Sprite
{
public:
	Sprite(int currX, int currY, std::string file, SDL_Renderer* ren);
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y, int w, int h, int offX, int offY, int advance);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::pair<std::string, std::string>, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	void show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string sequence);


// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:

	int currX, currY;		// the coordinates of the sprite relative to the window
	SDL_Renderer* renderer;

	struct frame
	{
		int x;
		int y;
		int w;
		int h;
		int offsetX;  // TO THE COLLISION GROUP
		int offsetY;  // currX - offsetX, currY - offsetY will be the upper left corner
		int advance;
		SDL_Texture* texture;
	};
	std::vector<frame> frames;

	std::pair<std::string, std::string> currentSequence;
	std::map<std::pair<std::string, std::string>, std::vector<int>> sequenceList;
	int sequenceIndex;

	frame getCurrentFrame(); // For the collision detection group

};