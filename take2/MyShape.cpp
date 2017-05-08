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
	m_previousPosition = myBodyDef.position;
	m_b2body = world->CreateBody(&myBodyDef);


	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_convert->scaleNumber(m_radius); //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 2;
	myFixtureDef.friction = 0.01;
	myFixtureDef.restitution = 0.1;
	m_b2body->CreateFixture(&myFixtureDef);
	m_b2body->SetFixedRotation(true);

	//set up sf circle to match the box2d circleShape
	m_sfcircleShape.setPosition(m_posX, m_posY);
	m_sfcircleShape.setFillColor(m_colour);
	m_sfcircleShape.setRadius(m_radius);
	m_sfcircleShape.setOrigin(m_radius, m_radius);

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

void MyShape::Putt(int force)
{
	m_b2body->ApplyLinearImpulseToCenter(b2Vec2(force, 0), true);
}

void MyShape::Jump(int force)
{
	m_b2body->ApplyLinearImpulseToCenter(b2Vec2(0, force), true);
}

///not working atm due to calls being in same state as the reset of m_previousPosition
bool MyShape::isMoving()
{
	if (m_b2body->GetPosition() != m_previousPosition)
	{
		m_previousPosition = m_b2body->GetPosition();
		return true;
	}
	else
	{
		return false;
	}
}


void MyShape::Update()
{
	b2Vec2 b2BallPos(m_b2body->GetPosition());
	//std::cout << "ball pos: " << b2BallPos.x << ", " << b2BallPos.y << std::endl;

	sf::Vector2f sfBallPos(m_convert->box2DXToCanvas(b2BallPos.x), m_convert->box2DYToCanvas(b2BallPos.y));
	m_sfcircleShape.setPosition(sfBallPos);
	//std::cout << "ball pos: " << sfBallPos.x << ", " << sfBallPos.y << std::endl;
	
	m_sfcircleShape.setRotation(m_convert->radiansToDegrees(m_b2body->GetAngle()));
}

b2Body * MyShape::GetBody()
{
	return m_b2body;
}

void MyShape::Draw(sf::RenderWindow & window)
{
	
	window.draw(m_sfcircleShape);
}

b2Vec2 MyShape::GetBodyPosition()
{
	return m_b2body->GetPosition();
}


MyShape::~MyShape()
{
}
