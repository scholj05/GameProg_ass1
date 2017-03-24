#include "Conversion.h"



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

Conversion::~Conversion()
{
}
