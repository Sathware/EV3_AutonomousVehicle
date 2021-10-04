#pragma once
#include "Vec.h"
#include "EV3_Motor.h"

class Navigator
{
private:
	Vec toDestination;
	Vec direction;
	int degrees;// valid values are [0, 360)
	void makeTerminal(int& invalidAngle);
	static constexpr char speed = 10;
public:
	Navigator(Vec destination); //Robot must face directly towards destination
	bool Turn(const int degreesIn); //Positive rotate left, negative rotate right, must be between [0, 360)
	bool FaceDestination();
	bool Stop();
	bool MoveToDestination();
};