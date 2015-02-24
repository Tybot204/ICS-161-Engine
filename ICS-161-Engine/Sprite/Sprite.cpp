#include <SDL.h>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "Sprite.h"
#include "SDL_image.h"
#include <stdexcept>

namespace
{
	std::vector<std::string> split_string(std::string s, const std::string& delim)
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
	std::string strip(const std::string& s, const std::string& delim)
	{
		int first = s.find_first_not_of(delim);
		int last = s.find_last_not_of(delim);
		return s.substr(first, (last - first + 1));
	}
	std::string get_quoted(const std::string& s)
	{
		if (s.find_first_of('"') == std::string::npos)
			return s;
		return s.substr(s.find_first_of('"') + 1, s.find_last_of('"') - s.find_first_of('"') - 1);
	}
}

Sprite::Sprite(int currX, int currY, std::string file, SDL_Renderer* ren)
	: currX{ currX }, currY{ currY }, renderer{ ren }, sequenceIndex{ 0 }
{
	IMG_Init(IMG_INIT_PNG);
	std::ifstream input;
	input.open(file);
	if (input.fail())
		throw std::exception("Could not open the file");
	std::string line, root;
	std::pair<std::string, std::string> sequence;
	if (file.rfind("\\") != std::string::npos)
		root = file.substr(0, file.rfind("\\") + 1);
	else
		root = "";
	std::vector<std::string> str_params;
	SDL_Texture* tex;
	std::map<std::string, int> vars;
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.find_first_not_of(' ') != std::string::npos)
		{
			int params[7] = { 0, 0, 0, 0, 0, 0, 1 };
			int param_size = 7;
			line = line.substr(line.find_first_not_of(" \t\r\n\v"));
			switch (line[0])
			{
			case '?':
				vars[strip(line.substr(1, line.find('=') - 1), " \t\r\n\v")] = std::stoi(line.substr(line.find('=') + 1));
				break;
			case '>':
				str_params = split_string(line.substr(1), ":");
				sequence = std::make_pair(strip(str_params[0], " \r\v\n\t"), strip(str_params[1], " \r\v\n\t"));
				break;
			case 'F':
			case 'f':
				tex = IMG_LoadTexture(ren, (root + get_quoted(strip(line.substr(line.find('=') + 1), " \r\n\t\v"))).c_str());
				break;
			case ':':
				sequence = std::make_pair(strip(line.substr(1), " \r\v\n\t"), strip(line.substr(1), " \r\v\n\t"));
				break;
			case '/':
				break;
			default:
				str_params = split_string(line, ",");
				for (auto i = 0u; i < str_params.size(); ++i)
					str_params[i] = strip(str_params[i], " \r\t\v\n");
				if (str_params.size() == 1)
				{
					int siz = -std::stoi(str_params[0]);
					addFrameToSequence(sequence, makeFrame(NULL, 0, 0, 0, 0, 0, 0, siz >= 0 ? -1 : siz));
					break;
				}
				if (str_params.size() == 4)
					param_size = 4;
				if (str_params.size() == 5)
				{
					params[6] = vars.count(str_params[4]) ? vars[str_params[4]] : std::stoi(str_params[4]);
					param_size = 4;
				}
				if (str_params.size() == 6)
					param_size = 6;
				for (int i = 0; i < param_size; ++i)
					params[i] = vars.count(str_params[i]) ? vars[str_params[i]] : std::stoi(str_params[i]);
				for (int i = 0; i < params[6]; ++i)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 1));
				if (params[6] <= 0)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 0));
			}
		}
	}
	input.close();
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

int Sprite::addFrameToSequence(std::pair<std::string, std::string> seqName, int frameIndex)
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
	while (sequence != currentSequence.second || (unsigned int)sequenceIndex >= sequenceList[currentSequence].size())
	{
		currentSequence.first = currentSequence.second;
		currentSequence.second = sequence;
		sequenceIndex = 0;
	}
	int frame_num = sequenceList[currentSequence][sequenceIndex];
	if (frames[frame_num].texture == NULL)
	{
		sequenceIndex += frames[frame_num].advance;
		frame_num = sequenceList[currentSequence][sequenceIndex];
	}
	show(frame_num);
	sequenceIndex += frames[frame_num].advance;
}

Sprite::frame Sprite::getCurrentFrame()
{
	return frames[sequenceList[currentSequence][sequenceIndex]];
}