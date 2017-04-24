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
	Conversion(float scale, float scaledWidth, float scaledHeight);

	float canvasYToBox2D(float y);
	float canvasXToBox2D(float x);
	float box2DYToCanvas(float y);
	float box2DXToCanvas(float x);
	float scaleNumber(float n) { return n * scale; };
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);

	int getRandomInt(int min, int max);
	float getRandomFloat(float min, float max);

	float getScale();

	float getPI();

	~Conversion();
};

