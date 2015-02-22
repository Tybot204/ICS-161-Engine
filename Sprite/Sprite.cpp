#include <SDL.h>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include "Sprite.h"
#include "SDL_image.h"

namespace
{
	std::vector<std::string> split_string(std::string s, std::string delim)
	{
		std::vector<std::string> result;
		int pos;
		while ((pos = s.find(delim)) != std::string::npos)
		{
			result.push_back(s.substr(0, pos));
			s.erase(0, pos + delim.length());
		}
		if (s != "")
			result.push_back(s);
		return result;
	}
}

Sprite::Sprite(std::string file, SDL_Renderer* ren)
	: currX{ 0 }, currY{ 0 }, renderer{ ren }, sequenceIndex{ 0 }
{
	IMG_Init(IMG_INIT_PNG);
	std::ifstream input;
	input.open(file);
	std::string line, sequence, root;
	if (file.rfind("\\") != std::string::npos)
		root = file.substr(0, file.rfind("\\") + 1);
	else
		root = "";
	std::vector<std::string> str_params;
	SDL_Texture* tex;
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.find_first_not_of(' ') != std::string::npos)
		{
			int params[7] = { 0, 0, 0, 0, 0, 0, 1 };
			int param_size = 7;
			line = line.substr(line.find_first_not_of(" \t\r\n"));
			switch (line[0])
			{
			case 'F':
			case 'f':
				tex = IMG_LoadTexture(ren, (root + line.substr(line.find('=') + 1)).c_str());
				break;
			case ':':
				sequence = line.substr(1);
				break;
			case '/':
				break;
			default:
				str_params = split_string(line, ",");
				if (str_params.size() == 1)
				{
					addFrameToSequence(sequence, makeFrame(NULL, 0, 0, 0, 0, 0, 0, -std::abs(std::stoi(str_params[0])) + 1));
					break;
				}
				if (str_params.size() == 4)
					param_size = 4;
				if (str_params.size() == 5)
				{
					params[6] = std::stoi(str_params[4]);
					param_size = 4;
				}
				if (str_params.size() == 6)
					param_size = 6;
				for (int i = 0; i < param_size; ++i)
					params[i] = std::stoi(str_params[i]);
				for (int i = 0; i < params[6]; ++i)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 1));
				if (params[6] <= 0)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 0));
			}
		}
	}
}

Sprite::~Sprite(void)
{
	for(frame f : frames)
		SDL_DestroyTexture(f.texture);
}

void Sprite::setPos(int x, int y)
{
	currX = x;
	currY = y;
}

void Sprite::movex(int delta)
{
	currX += delta;
}

void Sprite::movey(int delta)
{
	currY += delta;
}

int Sprite::getX()
{
	return currX;
}

int Sprite::getY()
{
	return currY;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y, int w, int h, int offX, int offY, int advance)
{
	frame f = { x, y, w, h, offX, offY, advance, texture };
	frames.push_back(f);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList[seqName].size();
}

void Sprite::show(int frameIndex)
{
	frame f = frames[frameIndex];
	SDL_Rect src = { f.x, f.y, f.w, f.h };
	SDL_Rect dst = { currX - f.offsetX, currY - f.offsetY, f.w, f.h };
	SDL_RenderCopy(renderer, f.texture, &src, &dst);
}

void Sprite::show(std::string sequence)
{
	if (sequence != oldseq)
	{
		oldseq = sequence;
		sequenceIndex = -1;
	}
	frame f = frames[sequenceList[sequence][(sequenceIndex + 1) % sequenceList[sequence].size()]];
	if ((sequenceIndex += f.advance) < 0)
		sequenceIndex = 0;
	show(sequenceList[sequence][sequenceIndex % sequenceList[sequence].size()]);
}