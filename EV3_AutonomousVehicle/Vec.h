#pragma once

class Vec
{
private:
	float x;
	float y;
public:
	/* Constructors */
	Vec(float x, float y);
	Vec(float angle, float magnitude);

	/* Operators */
	Vec operator+(const Vec& other) const; //Return vector that equals 'this' plus 'other'
	Vec operator-(const Vec& other) const; //Returns vector that equals 'this' minus 'other' 
	Vec operator*(const float scalar) const; //Returns a vector that equals 'this' scaled by 'scalar'
	Vec& operator+=(const Vec& other); //Adds 'other' to 'this' and updates value of self
	Vec& operator-=(const Vec& other); //Subtracts 'other' from 'this' and updates value of self
	Vec& operator*=(const float scalar); //scales 'this' by 'scalar'
	bool operator==(const Vec& other) const; //Returns whether two vectors have the same x and y
	
	/* Vector Properties */
	float GetAngle() const; //Returns angle relative in radians
	float GetMagnitudeSq() const; //Return the square of the magnitude
	float GetMagnitude() const; //Return magnitude
	
	/* Vector Manipulation */
	Vec GetNormalized() const;
	Vec& Normalize();
};