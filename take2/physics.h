#pragma once
#include <list>
#include <cmath>
#include <iostream>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Conversion.h"



class CreateShape
{
private:
	b2World * m_world;
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_bodyShape;
	b2FixtureDef * m_bodyFix;
	sf::RectangleShape m_shape; //SFML shape
	Conversion convert;

	//predefined arrays for adding coordinates to b2polygonShapes
	b2Vec2 m_octagon[8];
	b2Vec2 m_heptagon[7];
	b2Vec2 m_hexagon[6];
	b2Vec2 m_pentagon[5];
	b2Vec2 m_square[4];
	b2Vec2 m_triangle[3];

	bool m_debug;

public:
	CreateShape();
	CreateShape(bool debug);
	~CreateShape();


	///creates symmetrical by plotting evenly spaces points on a circle's circumference
	b2PolygonShape calculateShape(b2Vec2 position, float radius, int verticeCount);

	///Currently takes canvas inputs rather than converted inputs due to calculations needing to be done before conversion
	b2PolygonShape calculateRectangle(b2Vec2 position, float width, float height);

	b2PolygonShape calculateRandomShape(b2Vec2 position);

	///returns the correct predefined-length array
	b2Vec2 * getb2Vec2(int length);

	///adds the 3 parameters to bodyFixture and returns the updated fixture. purely for cleaning up main method
	b2FixtureDef setFixture(float Density, float Friction, float Restitution);

	///for debug printout toggle
	void setDebug(bool debug);

	void testMethod(b2World * world);


};
