#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <map>

typedef std::pair<double, double> Vector;

class Sprite
{
public:
	typedef std::pair<std::string, std::string> Sequence;

	Sprite(double currX, double currY, std::string file, SDL_Renderer* ren);
	~Sprite(void);

	void	setPos(int x, int y);
	void	movex(double delta);
	void	movey(double delta);
	void	setVX(double vx);
	void	setVY(double vy);
	void	setAX(double ax);
	void	setAY(double ay);
	double	getX()  const;
	double	getY()  const;
	double	getVX() const;
	double	getVY() const;
	double	getAX() const;
	double	getAY() const;

	// Sets the Sprite's coordinates relative to its top/bottom/left/right
	void setTop(double top);
	void setBottom(double bottom);
	void setLeft(double left);
	void setRight(double right);

	// makeFrame returns the unique index of the frame
	int		makeFrame(SDL_Texture* texture, int x, int y, int w, int h, int offX, int offY, int advance, std::vector<SDL_Rect> hitboxes);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int		addFrameToSequence(std::pair<std::string, std::string>, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	void	show(int frameIndex, int hitboxes);
	// show(string) cycles through all frames in the specified sequence, one per call
	void	show(std::string sequence, int hitboxes);

	void	update();

	SDL_Rect getBoundary();

	std::vector<SDL_Rect> getHitboxes();
	/*
		For the physics group
		You can iterate through all of a sprite's current hitboxes by doing
		for ( SDL_Rect hitbox : my_sprite.getHitboxes() )
		{
			// Do stuff here
		}
	*/

private:

	SDL_Renderer* renderer;

	struct frame
	{
		int	x;
		int y;
		int w;
		int h;
		int offsetX;  // TO THE COLLISION GROUP
		int offsetY;  // position.first - offsetX, position.second - offsetY will be the upper left corner
		int advance;  // make sure to take into account velocities, so objects can't phase through each other
		SDL_Texture* texture;
		std::vector<SDL_Rect> hitboxes;
	};
	std::vector<frame> frames;

	Sequence currentSequence;
	std::map<Sequence, std::vector<int>> sequenceList;
	int sequenceIndex;

	void showHitboxes();

	// Converts a hitbox that is relative to the frame
	// to a hitbox that is relative to the world

	// Hitboxes are stored as X, Y, W, H
	SDL_Rect getEffectiveHitbox(SDL_Rect hitbox) const;
	frame getCurrentFrame(); // For the collision detection group and physics

	Vector position;		// the coordinates of the sprite relative to the window
	Vector velocity;
	Vector acceleration;

	//double mass; Not sure if necessary
};

bool collide(Sprite& a, Sprite& b);