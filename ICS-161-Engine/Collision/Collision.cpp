#include "Collision.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

/* Player Values */
double walk_speed = 2;
double run_speed = 2 * walk_speed;
double grounded_speed = 0;
double fall_speed = -11;
double jump_speed = 4;

/* Projectile Values */
double vert_bounce = -6;
double horiz_bounce = -3;
double proj_accelX = 0.1;
std::vector<double> reflectfront = { -3, -3, -0.1 };
std::vector<double> reflectback = { 3, 3, 0.1 };
std::vector <double> reflecttop = { 6, 0.1, 0.1 };

double setMoveSpeed(double speed, bool left, bool right)
{
	if (left)
	{
		speed = -speed;
	}

	return speed;
}

double setStateSpeed(double speed)
{
	return speed;
}

double setBounceSpeed(double speed, std::string event)
{
	if (event == "ground")
	{
		return speed;
	}

	return speed;
}

void checkBounds(double posX, double posY, double screenWidth, double screenHeight, Sprite *sprite)
{
	if (posX >= screenWidth)
	{
		sprite->setVX(reflectfront[0]);
		sprite->setVY(reflectfront[1]);
		sprite->setAX(reflectfront[2]);
	}

	else if (posX <= 0)
	{
		sprite->setVX(reflectback[0]);
		sprite->setVY(reflectback[1]);
		sprite->setAX(reflectback[2]);
	}

	else if (posY <= 0)
	{
		sprite->setVY(reflecttop[0]);
		sprite->setAX(reflecttop[1]);
		sprite->setAY(reflecttop[2]);
	}

	else if (posY >= screenHeight)
	{
		sprite->setVY(sprite->getVY()*-1);
		sprite->setAY(reflectfront[2]);
	}

}

int collisionHit(Sprite *sprite1, Sprite *sprite2, int score)
{
	if (collide(*sprite1, *sprite2))
	{
		sprite2->setVY(sprite2->getVY()*-2);
		sprite2->setVX(sprite2->getVX()*-2);
		if (score > 0)
		{
			score--;
		}
	}
	return score;
}

std::vector<double> Reflect(std::vector<double> reflect)
{
	return reflect;
}
//
//int setGroundedSpeed(int speed)
//{
//	return grounded_speed;
//}
//
//int setJumpSpeed(int speed)
//{
//	return jump_speed;
//}
//
//int setFallSpeed(int speed)
//{
//	return fall_speed;
//}

