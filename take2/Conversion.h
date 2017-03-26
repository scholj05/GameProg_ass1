#pragma once
class Conversion
{
private:
	float scale, scaledWidth, scaledHeight;
	const double m_PI = 3.14159265359;

public:
	Conversion();
	Conversion(float scale, float scaledWidth, float scaledHeight);

	float canvasYToBox2D(float y);
	float canvasXToBox2D(float x);
	float box2DYToCanvas(float y);
	float box2DXToCanvas(float x);
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);

	float getPI();

	~Conversion();
};

