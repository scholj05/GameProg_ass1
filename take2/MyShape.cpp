#include "MyShape.h"



MyShape::MyShape(float posX, float posY, int sides, b2BodyType bodyType, int size, sf::Color colour, b2World* m_world)
{
	//get converted numbers for the b2 objects
	b2Vec2 b2Position(m_convert.canvasXToBox2D(posX), m_convert.canvasYToBox2D(posY));
	float b2Size(m_convert.scaleNumber(size));
	//default values, can be changed by setFixture method afterwards.
	m_b2fixtureDef.density = 1;
	m_b2fixtureDef.friction = 1;
	m_b2fixtureDef.restitution = 1;

	m_b2bodyDef->type = bodyType;
	m_b2bodyDef->position.Set(posX, posY);

	if (sides == 0)
	{
		m_isCircle = true;
		m_b2circleShape.m_radius = b2Size;
		m_b2circleShape.m_p = b2Position;
		m_b2fixtureDef.shape = &m_b2circleShape;

		m_sfcircleShape = new sf::CircleShape;
		m_sfcircleShape->setRadius(size);
		m_sfcircleShape->setOrigin(size / 2, size / 2);
		m_sfcircleShape->setPosition(sf::Vector2f(posX, posY));
		m_sfcircleShape->setFillColor(colour);
	}
	else if (sides >= 3 && sides <= 8)
	{
		m_isCircle = false;
		m_b2polyShape = m_createShape.calculateShape(b2Position, b2Size, sides);
		m_b2fixtureDef.shape = &m_b2polyShape;

		m_sfconvexShape->setPointCount(sides);
		for (int i = 0; i < m_b2polyShape.GetVertexCount(); i++)
		{
			m_sfconvexShape->setPoint(i, sf::Vector2f(m_convert.box2DXToCanvas(m_b2polyShape.GetVertex(float(i)).x), m_convert.box2DYToCanvas(m_b2polyShape.GetVertex(float(i)).y)));
		}
		m_sfconvexShape->setOrigin(size / 2, size / 2);
		m_sfconvexShape->setFillColor(colour);
	}
}




void MyShape::Update()
{
	if (m_isCircle)
	{
		m_sfcircleShape->setPosition(m_b2body->GetPosition().x, m_b2body->GetPosition().y);
	}
	else
	{
		for (int i = 0; i < m_b2polyShape.GetVertexCount(); i++)
		{
			m_sfconvexShape->setPoint(i, sf::Vector2f(m_convert.box2DXToCanvas(m_b2polyShape.GetVertex(float(i)).x), m_convert.box2DYToCanvas(m_b2polyShape.GetVertex(float(i)).y)));
		}
	}
	
}

void MyShape::Draw(sf::RenderWindow & window)
{
	if (m_isCircle)
		window.draw(*m_sfcircleShape);
	else
		window.draw(*m_sfconvexShape);
}


MyShape::~MyShape()
{
}
