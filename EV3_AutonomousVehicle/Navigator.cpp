#include "Navigator.h"
#include <cmath>
#define left E_Port_A
#define right E_Port_D
#define epsilon .00001 //constexpr are not allowed so this is the only way; max error in floats
using namespace ev3_c_api;

Navigator::Navigator(Vec destination)
	: toDestination(destination), direction(1.0f, 0.0f), theta(0.0f)
{}

bool Navigator::Turn(const float dtheta, const char speed)
{
	if (speed > 100 || std::abs(dtheta) <= epsilon)
		return false;

	theta += dtheta;//update stored angle representing direction
	direction = Vec(cosf(theta), sinf(theta));// !!!!!! CAN MAKE MORE EFFICIENT !!!!!!!!!!!!!!
	makeTerminal(theta);//ensure that theta is an angle between [0, 2pi)
	if (dtheta > 0)
		return SpeedTwoMotors_Time(left, -speed, right, speed, toMilliSec(dtheta, speed));
	else
		return SpeedTwoMotors_Time(left, speed, right, -speed, toMilliSec(dtheta, speed));
}

int Navigator::toMilliSec(const float angle, const char speed) const
{
	//return int(abs(angle) * radiusInCM / (speed in cm per millisecond)) for time to spin in milliseconds
	return 0;
}

void Navigator::makeTerminal(float& invalidAngle)
{
	while (invalidAngle >= 2 * PI)
		invalidAngle -= 2 * PI;

	while (invalidAngle < 0)
		invalidAngle += 2 * PI;
}

bool Navigator::isFacingDestination()
{
	return std::abs(theta - toDestination.GetAngle()) <= epsilon;
}

bool Navigator::FaceDestination()
{
	if (!isFacingDestination())//If robot is noticeably off from destination angle
		return Turn(toDestination.GetAngle() - theta);//turns from current angle 'theta' to destination
	return true;
}

bool Navigator::Stop() const
{
	return StopMotorAll();
}

bool Navigator::isAtDestination() const
{
	return toDestination.GetMagnitude() > epsilon;
}

bool Navigator::moveToDestination(const char speed)
{
	if (speed < 0)
		return false;

	FaceDestination();
	int millis = int(toDestination.GetMagnitude() /* / speed in cm per millisec */);
	toDestination -= direction /* * millis * speed in cm per millisec*/;
	return SpeedTwoMotors_Time(left, speed, right, speed, millis);
}