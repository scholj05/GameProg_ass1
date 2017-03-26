#include "physics.h"

Shape::Shape()
{

}

Shape::Shape(b2World & world, b2BodyType bodyType, b2Vec2 position, float radius, int verticeCount, float Density, float Friction, float Restitution) : m_world(&world)
{
	
	b2PolygonShape myShape = calculateShape(position, radius, verticeCount);
	m_bodyDef.type = bodyType;
	//m_bodyDef.position = position; ///not needed if vertices define location?
	m_bodyFix = new b2FixtureDef;
	m_bodyFix->shape = &myShape;	
	m_bodyFix->density = Density;
	m_bodyFix->friction = Friction;
	m_bodyFix->restitution = Restitution;
	m_body->CreateFixture(m_bodyFix);

	m_body = world.CreateBody(&m_bodyDef);

}

b2PolygonShape Shape::calculateShape(b2Vec2 position, float radius, int verticeCount)
{
	b2PolygonShape tempShape;

	/// only accept valid vertice count for Box2D.
	int m_verticeCount;
	if (verticeCount < 4)
		m_verticeCount = 3;
	else if (verticeCount > 8)
		m_verticeCount = 8;
	else
		m_verticeCount = verticeCount;

	/// set length to predefined length array(avoid dynamic-length list for conversion avoidance).
	b2Vec2 * verticeArray = getb2Vec2(m_verticeCount);


	float m_angle = 0;
	/// find equally spaced points on the circumference of a circle.
	for (int i = 0; i < m_verticeCount; i++)
	{
		m_angle = i * 2 * convert.getPI() / verticeCount;
		
		float tempX = position.x + radius * cos(m_angle);
		float tempY = position.y + radius * sin(m_angle);
		
		verticeArray[i] = b2Vec2(tempX, tempY);
		std::cout << verticeArray[i].x << ", " << verticeArray[i].y << std::endl;///debug
	}
	/// set the empty shape to the array of vertices and return it.
	tempShape.Set(verticeArray, m_verticeCount);
	return tempShape;
}

b2PolygonShape Shape::calculateRectangle(b2Vec2 position, float width, float height)
{
	b2PolygonShape tempShape;
	b2Vec2 tempArray[4] =
	{
		b2Vec2(position.x - width / 2, position.y - height / 2),
		b2Vec2(position.x + width / 2, position.y - height / 2),
		b2Vec2(position.x - width / 2, position.y + height / 2),
		b2Vec2(position.x + width / 2, position.y + height / 2),
	};
	std::cout << "Debug:calculateRectangle(): " << std::endl <<
		"(" << tempArray[0].x << ", " << tempArray[0].y << ")," << std::endl <<
		"(" << tempArray[1].x << ", " << tempArray[1].y << ")," << std::endl <<
		"(" << tempArray[2].x << ", " << tempArray[2].y << ")," << std::endl <<
		"(" << tempArray[3].x << ", " << tempArray[3].y << ")," << std::endl;

	tempShape.Set(tempArray, 4);
	return tempShape;
}

/// returns a b2Vec2 array of length equal to input parameter.
b2Vec2 * Shape::getb2Vec2(int length)
{
	b2Vec2* myVec;
	if (length == 3)
		myVec = m_triangle;
	else if (length == 4)
		myVec = m_square;
	else if (length == 5)
		myVec = m_pentagon;
	else if (length == 6)
		myVec = m_hexagon;
	else if (length == 7)
		myVec = m_heptagon;
	else if (length == 8)
		myVec = m_octagon;
	else
	{
		std::cout << "invalid length of vector array passed as parameter: physics.cpp (b2Vec2* Shape::getb2Vec2(int length)" << std::endl;
		myVec = m_octagon;
	}
	return myVec;
}

b2FixtureDef Shape::setFixture(float Density, float Friction, float Restitution)
{
	b2FixtureDef m_fixture;
	m_fixture.density = Density;
	m_fixture.friction = Friction;
	m_fixture.restitution = Restitution;
	return m_fixture;
}

void Shape::addToWorld(b2World & world)
{
	
	m_body = world.CreateBody(&m_bodyDef);
}

Shape::~Shape()
{
}