#pragma once
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "physics.h"
#include "Conversion.h"

class MyShape
{
private:
	float m_radius;
	b2BodyType m_bodyType;
	float m_posX, m_posY;
	sf::Color m_colour;
	
	CreateShape m_createShape;
	Conversion * m_convert;

	//b2World * m_world;
	b2Body * m_b2body;
	b2BodyDef * m_b2bodyDef;
	b2FixtureDef m_b2fixtureDef;
	b2PolygonShape m_b2polyShape;
	b2CircleShape m_b2circleShape;

	sf::CircleShape m_sfcircleShape;

	bool m_isCircle;

public:
	MyShape(float posX, float posY, b2BodyType bodyType, int size, sf::Color colour, b2World * m_world, Conversion &convert);
	
//	b2Body GetBody() { return *m_b2body; };
//	b2BodyDef GetBodyDef() { return *m_b2bodyDef; };
//	b2FixtureDef GetFixtureDef() { return m_b2fixtureDef; };
	
	void Update();
	void Draw(sf::RenderWindow & window);
	~MyShape();
};

