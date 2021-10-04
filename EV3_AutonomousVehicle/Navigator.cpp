#include "Navigator.h"
#include <cmath>
#define left E_Port_A
#define right E_Port_D
using namespace ev3_c_api;

void Navigator::makeTerminal(int& invalidAngle)
{
	while (invalidAngle >= 360)
		invalidAngle -= 360;
	while (invalidAngle < 0)
		invalidAngle += 360;
}

Navigator::Navigator(Vec destination)
	: toDestination(destination), direction(1.0f, 0.0f), degrees(0), speed(10)
{
}

bool Navigator::Turn(const int degreesIn)//NOT TESTED - BEHAVIOR UNKNOWN
{
	degrees += degreesIn;
	makeTerminal(degrees);
	direction = Vec( cosf(degrees * 3.141592653589793238463f / 180.0f), 
				  sinf(degrees * 3.141592653589793238463f / 180.0f) );//converts degrees to radians and inputs it into sine and cosine respectively
	return SpeedMotor_RotationAngle(left, -speed, degreesIn) 
		&& SpeedMotor_RotationAngle(right, speed, degreesIn);
}

bool Navigator::FaceDestination()//Depends on UNTESTED FUNCTION
{
	return Turn(toDestination.GetAngle() - degrees);
}

bool Navigator::Stop()
{
	return StopMotorAll();
}

bool Navigator::MoveToDestination()// NOT DONE IMPLEMENTING
{
	if (degrees != toDestination.GetAngle())
		FaceDestination();

}