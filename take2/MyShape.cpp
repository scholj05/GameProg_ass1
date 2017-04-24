#include "MyShape.h"



MyShape::MyShape(float posX, float posY, int sides, b2BodyType bodyType, int size, sf::Color colour)
{
	//default values, can be changed by setFixture method afterwards.
	m_b2fixtureDef.density = 1;
	m_b2fixtureDef.friction = 1;
	m_b2fixtureDef.restitution = 1;

	m_b2bodyDef.type = bodyType;
	m_b2bodyDef.position.Set(posX, posY);

	if (sides == 0)
	{
		m_b2circleShape.m_radius = size;
		m_b2circleShape.m_p = b2Vec2(posX, posY);
		m_b2fixtureDef.shape = &m_b2circleShape;
	}
	else if (sides >= 3 && sides <= 8)
	{
		//m_b2polyShape = b2PolygonShape()
	}
	m_b2body = m_world->CreateBody(&m_b2bodyDef);
	m_b2body->CreateFixture(&m_b2fixtureDef);

}


MyShape::~MyShape()
{
}
