#pragma once
#include <iostream>
#include <vector>

extern double walk_speed;
extern double run_speed;
extern double grounded_speed;
extern double fall_speed;
extern double jump_speed;
extern std::vector<double> reflectfront;
extern std::vector<double> reflectback;
extern std::vector<double> reflecttop;
//float angle;

//std::pair<int, int> velocityI;
//std::pair<int, int> positionI;


double setMoveSpeed(double speed, bool left, bool right);
double setStateSpeed(double speed);
std::vector<double> Reflect(std::vector<double> reflect);
//int setGroundedSpeed(int speed);
//int setJumpSpeed(int speed);
//int setFallSpeed(int speed);