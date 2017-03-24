#include "physics.h"

Shape::Shape(b2World & world, b2BodyType bodyType, b2Vec2 position, float radius, int verticeCount)
{
	b2PolygonShape myShape = createShape(radius, verticeCount);
	m_bodyDef.type = bodyType;
	m_bodyDef.position = position;

}

b2PolygonShape Shape::createShape(float radius, float verticeCount)
{
	b2PolygonShape tempShape;

	static int arrayLength = verticeCount;
	b2Vec2 vertArray[arrayLength];

}