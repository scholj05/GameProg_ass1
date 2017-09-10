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

	b2Body * m_b2body;
	b2BodyDef * m_b2bodyDef;
	b2FixtureDef m_b2fixtureDef;
	b2PolygonShape m_b2polyShape;
	b2CircleShape m_b2circleShape;

	b2Vec2 m_previousPosition;

	sf::CircleShape m_sfcircleShape;

public:
	///constructor
	MyShape(float posX, float posY, b2BodyType bodyType, int size, sf::Color colour, b2World * m_world, Conversion &convert);

	///apply impulse on X axis
	void Putt(int force);

	///apply impulse on Y axis
	void Jump(int force);
	
	///Check if position is the same as last tick
	bool isMoving();
	
	///update sf shape to match box2d shape
	void Update();

	///return the b2body of the ball
	b2Body * GetBody();

	///draw the sf ball
	void Draw(sf::RenderWindow & window);

	///return b2 shape's position
	b2Vec2 GetBodyPosition();

	~MyShape();
};

