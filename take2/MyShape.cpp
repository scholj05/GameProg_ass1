/*
*	This file and its contents were written by the author, unless stated otherwise.
*	The code is in no way guaranteed to be in working condition,
*	nor does the author claim any responsibility for negative outcomes of running
*	the contents of this file.
*  Any use of this file must be done with the permission of the author.
*
*	@author		Jesse Schollitt
*/

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
	myFixtureDef.density = 2.0;
	myFixtureDef.friction = 1.0;
	myFixtureDef.restitution = 0.5;
	m_b2body->CreateFixture(&myFixtureDef);
	m_b2body->SetAngularDamping(5);

	//set up sf circle to match the box2d circleShape
	m_sfcircleShape.setPosition(m_posX, m_posY);
	m_sfcircleShape.setFillColor(m_colour);
	m_sfcircleShape.setRadius(m_radius);
	m_sfcircleShape.setOrigin(m_radius, m_radius);

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

	sf::Vector2f sfBallPos(m_convert->box2DXToCanvas(b2BallPos.x), m_convert->box2DYToCanvas(b2BallPos.y));
	m_sfcircleShape.setPosition(sfBallPos);
	
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
