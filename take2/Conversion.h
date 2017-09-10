/*
*	This file and its contents were written by the author, unless stated otherwise.
*	The code is in no way guaranteed to be in working condition,
*	nor does the author claim any responsibility for negative outcomes of running
*	the contents of this file.
*  Any use of this file must be done with the permission of the author.
*
*	@author		Jesse Schollitt
*/

#pragma once
#include <random>
class Conversion
{
private:
	float scale, scaledWidth, scaledHeight;
	const double m_PI = 3.14159265359;

	std::random_device rd;
	std::mt19937 generator;
	std::uniform_int_distribution<int> distributeInt;
	std::uniform_real_distribution<float> distributeFloat;

public:
	Conversion();

	///constructor with starting values to set scales
	Conversion(float scale, float scaledWidth, float scaledHeight);

	///convert SFML x coord to box2d x coord
	float canvasXToBox2D(float x);

	///convert SFML y coord to box2d x coord
	float canvasYToBox2D(float y);

	///convert box2d x coord to SFML x coord
	float box2DYToCanvas(float y);

	///convert box2d y coord to SFML y coord
	float box2DXToCanvas(float x);

	///multiply input by scale and return
	float scaleNumber(float n) { return n * scale; };

	///convert degrees to radians
	float degreesToRadians(float degrees);

	///convert radians to degrees
	float radiansToDegrees(float radians);

	///return a random integer within input range
	int getRandomInt(int min, int max);

	///return a random float within input range
	float getRandomFloat(float min, float max);

	///returns scale number
	float getScale();

	///returns Pi
	float getPI();

	~Conversion();
};

