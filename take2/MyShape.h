#pragma once
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

class MyShape
{
private:
	b2World * m_world;
	b2Body * m_b2body;
	b2BodyDef m_b2bodyDef;
	b2FixtureDef m_b2fixtureDef;
	b2PolygonShape m_b2polyShape;
	b2CircleShape m_b2circleShape;

	sf::ConvexShape m_sfconvexShape;
	sf::CircleShape m_sfcircleShape;

public:
	MyShape(float posX, float posY, int sides, b2BodyType bodyType, int size, sf::Color colour);
	~MyShape();
};

