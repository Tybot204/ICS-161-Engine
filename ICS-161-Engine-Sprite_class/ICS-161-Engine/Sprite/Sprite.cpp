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
#include <cmath>
#include <iostream>

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
		if (last == std::string::npos)
			return "";
		return s.substr(first, (last - first + 1));
	}

	std::string get_quoted(const std::string& s)
	{
		if (s.find_first_of('"') == std::string::npos)
			return s;
		return s.substr(s.find_first_of('"') + 1, s.find_last_of('"') - s.find_first_of('"') - 1);
	}

	double perform_op(double a, double b, char op)
	{
		switch (op)
		{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		}
		return 0;
	}

	double str_to_doub(const std::string& s, std::map<std::string, double>& vars)
	{
		return vars.count(s) ? vars[s] : std::stod(s);
	}

	double evaluate_expression(std::string s, std::map<std::string, double>& vars)
	{
		double accum = 0;
		int pos = 0;
		char op = '+';
		std::string num;
		while ((pos = s.find_first_of("/*+-")) != std::string::npos)
		{
			num = strip(s.substr(0, pos), " \r\t\v\n");
			if (num.length() == 0)
				num = "0";
			accum = perform_op(accum, str_to_doub(num, vars), op);
			op = s[pos];
			s = s.erase(0, pos + 1);
		}
		accum = perform_op(accum, str_to_doub(s, vars), op);
		return accum;
	}

	double getVectorSize(const Vector& vector)
	{
		return std::sqrt(vector.first * vector.first + vector.second * vector.second);
	}

	double vectorToAngle(const Vector& vector)
	{
		return std::atan2(vector.second, vector.first);
	}

	double degToRad(double degrees)
	{
		return M_PI * degrees / 180;
	}

	double radToDeg(double radians)
	{
		return 180 * radians / M_PI;
	}

	Vector addVectors(const Vector& a, const Vector& b)
	{
		return std::make_pair(a.first + b.first, a.second + b.second);
	}

	Vector subVectors(const Vector& a, const Vector& b)
	{
		return std::make_pair(a.first - b.first, a.second - b.second);
	}
}

Sprite::Sprite(double currX, double currY, std::string file, SDL_Renderer* ren)
	: renderer{ ren }, sequenceIndex{ 0 }, position{ std::make_pair(currX, currY) }
{
	//IMG_Init(IMG_INIT_PNG); Not sure if SDL_IMG is already initialized
	std::ifstream input;
	input.open(file);
	if (input.fail())
		//throw std::exception("Could not open the file");
		std::cout << "Could not open file." << std::endl;
	std::string line, root;
	std::pair<std::string, std::string> sequence;
	if (file.rfind("\\") != std::string::npos)
		root = file.substr(0, file.rfind("\\") + 1);
	std::vector<std::string> str_params;
	SDL_Texture* tex;
	std::map<std::string, double> vars;
	int hbparams[4] = { 0, 0, 0, 0 };
	int params[7] = { 0, 0, 0, 0, 0, 0, 1 };
	SDL_Rect hb;
	std::vector<SDL_Rect> hitboxes;
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.find_first_not_of(' ') != std::string::npos)
		{
			params[6] = 1;
			int param_size = 7;
			line = line.substr(line.find_first_not_of(" \t\r\n\v"));
			switch (line[0])
			{
			case '!':
				str_params = split_string(line.substr(1), ",");
				for (auto i = 0u; i < str_params.size(); ++i)
					str_params[i] = strip(str_params[i], " \r\t\v\n");
				for (int i = 0; i < 4; ++i)
					hbparams[i] = (int)evaluate_expression(str_params[i], vars);
				hb = { hbparams[0], hbparams[1], hbparams[2], hbparams[3] };
				hitboxes.push_back(hb);
				break;
			case '?':
				vars[strip(line.substr(1, line.find('=') - 1), " \t\r\n\v")] = std::stoi(line.substr(line.find('=') + 1));
				break;
			case '>':
				str_params = split_string(line.substr(1), ":");
				sequence = std::make_pair(strip(str_params[0], " \r\v\n\t"), strip(str_params[1], " \r\v\n\t"));
				break;
			case '$':
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
					int siz = (int)-evaluate_expression(str_params[0], vars);
					addFrameToSequence(sequence, makeFrame(NULL, 0, 0, 0, 0, 0, 0, siz >= 0 ? -1 : siz, hitboxes));
					break;
				}
				param_size = str_params.size() - str_params.size() % 2;
				if (str_params.size() % 2 == 1)
					params[6] = str_params[param_size].size() == 0 ? 1 : (int)evaluate_expression(str_params[param_size], vars);
				for (int i = 0; i < param_size; ++i)
					params[i] = str_params[i].size() == 0 ? params[i] : (int)evaluate_expression(str_params[i], vars);
				for (int i = 0; i < params[6]; ++i)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 1, hitboxes));
				if (params[6] <= 0)
					addFrameToSequence(sequence, makeFrame(tex, params[0], params[1], params[2], params[3], params[4], params[5], 0, hitboxes));
				hitboxes = std::vector<SDL_Rect>();
			}
		}
	}
	input.close();
}

Sprite::~Sprite(void)
{
	for (frame f : frames)
		SDL_DestroyTexture(f.texture);
}

void Sprite::setPos(int x, int y)
{
	position = std::make_pair(x, y);
}

void Sprite::movex(double delta)
{
	position.first += delta;
}

void Sprite::movey(double delta)
{
	position.second += delta;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y, int w, int h, int offX, int offY, int advance, std::vector<SDL_Rect> hitboxes)
{
	for (auto i = 0u; i < hitboxes.size(); ++i)
	{
		hitboxes[i].x -= offX;
		hitboxes[i].y -= offY;
	}
	frame f = { x, y, w, h, offX, offY, advance, texture, hitboxes };
	frames.push_back(f);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::pair<std::string, std::string> seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList[seqName].size();
}

SDL_Rect Sprite::getEffectiveHitbox(SDL_Rect hitbox) const
{
	hitbox.x += (int)position.first;
	hitbox.y += (int)position.second;
	return hitbox;
}

void Sprite::setTop(double top)
{
	SDL_Rect boundary = getBoundary();
	movey(top - boundary.y);
}

void Sprite::setBottom(double bottom)
{
	SDL_Rect boundary = getBoundary();
	movey(bottom - (boundary.y + boundary.h));
}

void Sprite::setLeft(double left)
{
	SDL_Rect boundary = getBoundary();
	movex(left - boundary.x);
}

void Sprite::setRight(double right)
{
	SDL_Rect boundary = getBoundary();
	movex(right - (boundary.x + boundary.w));
}

SDL_Rect Sprite::getBoundary()
{
	int up = INT_MAX, down = INT_MIN, left = INT_MAX, right = INT_MIN;
	for (SDL_Rect hitbox : getHitboxes())
	{
		if (hitbox.x < left)
			left = hitbox.x;
		if (hitbox.x + hitbox.w > right)
			right = hitbox.x + hitbox.w;
		if (hitbox.y < up)
			up = hitbox.y;
		if (hitbox.y + hitbox.h > down)
			down = hitbox.y + hitbox.h;
	}
	return { left, up, right - left, down - up };
}

std::vector<SDL_Rect> Sprite::getHitboxes()
{
	std::vector<SDL_Rect> result;
	for (SDL_Rect hitbox : getCurrentFrame().hitboxes)
		result.push_back(getEffectiveHitbox(hitbox));
	return result;
}

void Sprite::showHitboxes()
{
	Uint8 color[4];
	SDL_GetRenderDrawColor(renderer, &color[0], &color[1], &color[2], &color[3]);
	SDL_BlendMode blend;
	SDL_GetRenderDrawBlendMode(renderer, &blend);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &getBoundary());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 64);
	SDL_RenderFillRect(renderer, &getBoundary());
	for (SDL_Rect hb : getHitboxes())
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &hb);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 64);
		SDL_RenderFillRect(renderer, &hb);
	}
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
	SDL_SetRenderDrawBlendMode(renderer, blend);
}

void Sprite::show(int frameIndex, int hitboxes)
{
	frame f = frames[frameIndex];
	SDL_Rect src = { f.x, f.y, f.w, f.h };
	SDL_Rect dst = { (int)position.first - f.offsetX, (int)position.second - f.offsetY, f.w, f.h };
	SDL_RenderCopy(renderer, f.texture, &src, &dst);
	if (hitboxes)
		showHitboxes();
}

void Sprite::show(std::string sequence, int hitboxes)
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
	show(frame_num, hitboxes);
	sequenceIndex += frames[frame_num].advance;
	while (sequence != currentSequence.second || (unsigned int)sequenceIndex >= sequenceList[currentSequence].size())
	{
		currentSequence.first = currentSequence.second;
		currentSequence.second = sequence;
		sequenceIndex = 0;
	}
}

Sprite::frame Sprite::getCurrentFrame()
{
	if (sequenceList.count(currentSequence) == 0)
		return frames[0];
	return frames[sequenceList[currentSequence][sequenceIndex]];
}


// PHYSICS AND COLLISION CODE GOES HERE
// There are helper functions above

void Sprite::update()
{
	position = addVectors(position, velocity);
	velocity = addVectors(velocity, acceleration);
}

void Sprite::setVX(double vx)
{
	velocity.first = vx;
}

void Sprite::setVY(double vy)
{
	velocity.second = vy;
}

void Sprite::setAX(double ax)
{
	acceleration.first = ax;
}

void Sprite::setAY(double ay)
{
	acceleration.second = ay;
}

double Sprite::getX() const
{
	return position.first;
}

double Sprite::getY() const
{
	return position.second;
}

double Sprite::getVX() const
{
	return velocity.first;
}

double Sprite::getVY() const
{
	return velocity.second;
}

double Sprite::getAX() const
{
	return acceleration.first;
}

double Sprite::getAY() const
{
	return acceleration.second;
}

bool collide(Sprite& a, Sprite& b)
{
	for (SDL_Rect hba : a.getHitboxes())
		for (SDL_Rect hbb : b.getHitboxes())
			if (SDL_HasIntersection(&hba, &hbb) == SDL_TRUE)
				return true;
	return false;
}