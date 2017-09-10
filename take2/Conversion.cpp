/*
*	This file and its contents were written by the author, unless stated otherwise.
*	The code is in no way guaranteed to be in working condition,
*	nor does the author claim any responsibility for negative outcomes of running
*	the contents of this file.
*  Any use of this file must be done with the permission of the author.
*
*	@author		Jesse Schollitt
*/

#include "Conversion.h"

Conversion::Conversion()
{

}

Conversion::Conversion(float scale, float scaledWidth, float scaledHeight)
{
	this->scale = scale;
	this->scaledWidth = scaledWidth;
	this->scaledHeight = scaledHeight;
}

float Conversion::canvasYToBox2D(float y)
{
	float box2d = ((scaledHeight / 2) - (y * scale));
	return box2d;
}

float Conversion::canvasXToBox2D(float x)
{
	float box2d = (x * scale) - (scaledWidth / 2);
	return box2d;
}

float Conversion::box2DYToCanvas(float y) {
	return (scaledHeight - (y + (scaledHeight / 2.0f))) / scale;
}

float Conversion::box2DXToCanvas(float x)
{
	return (x + (scaledWidth / 2.0f)) / scale;
}

float Conversion::degreesToRadians(float degrees)
{
	return degrees * m_PI / 180;
}

float Conversion::radiansToDegrees(float radians)
{
	return radians * 180 / m_PI;
}

int Conversion::getRandomInt(int min, int max)
{
	generator = std::mt19937(rd());
	distributeInt = std::uniform_int_distribution<int>(min, max);
	return distributeInt(generator);
}

float Conversion::getRandomFloat(float min, float max)
{
	generator = std::mt19937(rd());
	distributeFloat = std::uniform_real_distribution<float>(min, max);
	return distributeFloat(generator);
}

float Conversion::getScale()
{
	return scale;
}

float Conversion::getPI()
{
	return m_PI;
}

Conversion::~Conversion()
{
}
