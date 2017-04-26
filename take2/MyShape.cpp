#include "MyShape.h"



MyShape::MyShape(float posX, float posY, b2BodyType bodyType, int size, sf::Color colour, b2World* world, Conversion &convert)
{
	m_b2body = NULL;
	m_radius = size;
	m_bodyType = bodyType;
	m_posX = posX, m_posY = posY;
	m_colour = colour;
	m_convert = &convert;


	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(m_convert->canvasXToBox2D(posX), m_convert->canvasYToBox2D(posY));
	m_b2body = world->CreateBody(&myBodyDef);

	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_convert->scaleNumber(m_radius); //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;
	m_b2body->CreateFixture(&myFixtureDef);

	//set up sf circle to match the box2d circleShape
	m_sfcircleShape.setPosition(m_posX, m_posY);
	m_sfcircleShape.setFillColor(m_colour);
	m_sfcircleShape.setRadius(m_radius);
	m_sfcircleShape.setOrigin(m_radius / 2, m_radius / 2);

	/*
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
	}*/
}




void MyShape::Update()
{
	
	/*if (m_isCircle)
	{
		m_sfcircleShape->setPosition(m_b2body->GetPosition().x, m_b2body->GetPosition().y);
	}
	else
	{
		for (int i = 0; i < m_b2polyShape.GetVertexCount(); i++)
		{
			m_sfconvexShape->setPoint(i, sf::Vector2f(m_convert.box2DXToCanvas(m_b2polyShape.GetVertex(float(i)).x), m_convert.box2DYToCanvas(m_b2polyShape.GetVertex(float(i)).y)));
		}
	}*/
	
}

void MyShape::Draw(sf::RenderWindow & window)
{
	b2Vec2 b2Pos(m_b2body->GetPosition());
	std::cout <<"ball pos: " << b2Pos.x << ", " << b2Pos.y << std::endl;
	m_sfcircleShape.setPosition(m_convert->box2DXToCanvas(b2Pos.x), m_convert->box2DYToCanvas(b2Pos.y));
	window.draw(m_sfcircleShape);
	/*if (m_isCircle)
		window.draw(*m_sfcircleShape);
	else
		window.draw(*m_sfconvexShape);*/
}


MyShape::~MyShape()
{
}
