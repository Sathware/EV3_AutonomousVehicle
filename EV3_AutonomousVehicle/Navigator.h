#pragma once
#include "Vec.h"
#include "EV3_Motor.h"
#include "EV3_Thread.h"

class Navigator
{
private:
	Vec toDestination;// in CM
	Vec direction;//in CM
	int theta;// valid values are [0, 2pi)
	void makeTerminal(int& invalidAngle);
	bool FaceDestination();//Face the direction of the destination
	bool isFacingDestination();//returns whther the robot is facing the destination
public:
	Navigator(Vec destination); //values relative to the front of the robot, and parameters are in cm
	bool Turn(const int dtheta, const char speed = 50); //Positive rotate left, negative rotate right, must be between [0, 2pi)
	bool Stop() const;//Stops all motion immediately
	//bool Interrupt();
	bool moveToDestination(const char speed = 50);//Moves toward destination at specified speed for specified duration
	bool isAtDestination() const;//Checks if the robot is near the destination
};