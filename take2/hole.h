#pragma once
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "physics.h"
#include "Conversion.h"
#include "MyShape.h"

class hole
{
private:
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

	sf::RectangleShape m_sfRectShape;
	sf::Texture m_flagTexture;
	sf::Sprite m_flag;

public:
	///constructor that sets position, size and colour, and saves pointers to objects/classes for later use
	hole(float posX, float posY, int size, sf::Color colour, b2World * m_world, Conversion &convert);

	///updates the SFML shape to match the box2d body in-case of a change of transform
	void Update();

	///check if the ball is in the hole
	bool IsWinCondition(MyShape * shape);

	///return the body pointer
	b2Body * GetBody();

	///draw the sfml part of the hole
	void Draw(sf::RenderWindow & window);

	///return hole position in box2d vec
	b2Vec2 GetPosition();

	~hole();
};

