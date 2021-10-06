#include "Navigator.h"
#include <cmath>
#define left E_Port_A
#define right E_Port_D
#define epsilon 3.0f //constexpr are not allowed so this is the only way; max error in cm
using namespace ev3_c_api;

Navigator::Navigator(Vec destination)
	: toDestination(destination), direction(1.0f, 0.0f), theta(0)
{}

int spinToWheelRotation(const int dtheta)
{
	//return int(radius of prototype * dtheta / radius of wheel)
	return 0;
}

int distanceToWheelRotations(const float distance)
{
	/* return int(distance / wheel radius * 180.0f / PI)*/
	return 0;
}

bool Navigator::Turn(const int dtheta, const char speed)
{
	if (speed > 100 || theta == 0)
		return false;

	theta += dtheta;//update stored angle representing direction
	direction = Vec(cosf(float(theta) * PI / 180.0f), sinf(float(theta) * PI / 180.0f));// !!!!!! CAN MAKE MORE EFFICIENT !!!!!!!!!!!!!!
	makeTerminal(theta);//ensure that theta is an angle between [0, 2pi)
	bool out = SpeedMotor_RotationAngle(left, speed, spinToWheelRotation(dtheta))
		&& SpeedMotor_RotationAngle(left, -speed, spinToWheelRotation(dtheta));
	EV3_Sleep(500);
	return out;
}

void Navigator::makeTerminal(int& invalidAngle)
{
	while (invalidAngle >= 360)
		invalidAngle -= 360;

	while (invalidAngle < 0)
		invalidAngle += 360;
}

bool Navigator::isFacingDestination()
{
	return theta - toDestination.GetAngle() != 0;
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

	/*while(isMotorBusy(left, E_MotorType_Large) || isMotorBusy(right, E_MotorType_Large))
	{}*/

	FaceDestination();
	float distance = toDestination.GetMagnitude();
	toDestination -= direction * distance;
	bool out = SpeedMotor_RotationAngle(left, speed, distanceToWheelRotations(distance)) 
		&& SpeedMotor_RotationAngle(right, speed, distanceToWheelRotations(distance));
	EV3_Sleep(500);
	return out;
}

