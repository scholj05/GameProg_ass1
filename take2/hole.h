#pragma once
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "physics.h"
#include "Conversion.h"
#include "MyShape.h"

class hole
{
private:
	//b2BodyType m_bodyType;
	float m_posX, m_posY;
	sf::Color m_colour;

	CreateShape m_createShape;
	Conversion * m_convert;

	b2World * m_world;
	b2Body * m_b2body;
	b2BodyDef * m_b2bodyDef;
	b2FixtureDef m_b2Fix1, m_b2Fix2, m_b2Fix3;
	b2PolygonShape m_b2Shape1, m_b2Shape2, m_b2Shape3;

	b2Vec2 m_previousPosition;

	sf::RectangleShape m_sfRectShape, m_sfFlagPole, m_sfFlag;

public:
	hole(float posX, float posY, int size, sf::Color colour, b2World * m_world, Conversion &convert);

	void Update();
	bool IsWinCondition(MyShape * shape);
	b2Body * GetBody();
	void Draw(sf::RenderWindow & window);
	b2Vec2 GetPosition();
	~hole();
};

