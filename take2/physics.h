#include <list>
#include <cmath>
#include <iostream>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Conversion.h"


class Shape
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

	bool data = true;

public:
	Shape();
	Shape(b2World & world);
	void ShapeSetWorld(b2World & world);
	b2Body* GetBody(); // Get Box2d body
	sf::Shape & GetShape();
	void update(); // Get SFML shape
	void ResetPosition(b2World & world); 
	void jump(float angle);
	~Shape();

	///redundant
	Shape(b2World & world, b2BodyType bodyType, b2Vec2 position, float radius, int verticeCount, float Density, float Friction, float Restitution);

	///creates symmetrical by plotting evenly spaces points on a circle's circumference
	b2PolygonShape calculateShape(b2Vec2 position, float radius, int verticeCount);

	///Currently takes canvas inputs rather than converted inputs due to calculations needing to be done before conversion
	b2PolygonShape calculateRectangle(b2Vec2 position, float width, float height);

	///returns the correct predefined-length array
	b2Vec2 * getb2Vec2(int length);

	///adds the 3 parameters to bodyFixture and returns the updated fixture. purely for cleaning up main method
	b2FixtureDef setFixture(float Density, float Friction, float Restitution);

	///redundant
	void addToWorld(b2World & world);


};
