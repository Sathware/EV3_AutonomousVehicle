#include "Vec.h"
#include <cmath>

Vec::Vec(float xIn, float yIn)
	: x(xIn), y(yIn)
{
}

Vec::Vec(float angle, float magnitude)
	: x(magnitude* cosf(angle)), y(magnitude* sinf(angle))
{
}

Vec Vec::operator+(const Vec& other) const
{
	return Vec(x + other.x, y + other.y);
}

Vec Vec::operator-(const Vec& other) const
{
	return Vec(x - other.x, y - other.y);
}

Vec Vec::operator*(const float scalar) const
{
	return Vec(x * scalar, y * scalar);
}

Vec& Vec::operator+=(const Vec& other)
{
	*this = *this + other;
	return *this;
}

Vec& Vec::operator-=(const Vec& other)
{
	*this = *this - other;
	return *this;
}

Vec& Vec::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

bool Vec::operator==(const Vec& other) const
{
	return x == other.x && y == other.y;
}

float Vec::GetAngle() const
{
	return atan2f(y, x);
}

float Vec::GetMagnitudeSq() const
{
	return x * x + y * y;
}

float Vec::GetMagnitude() const
{
	return sqrtf(GetMagnitudeSq());
}

Vec Vec::GetNormalized() const
{
	return *this * (1 / GetMagnitude());
}

Vec& Vec::Normalize()
{
	*this = *this * (1 / GetMagnitude());
	return *this;
}