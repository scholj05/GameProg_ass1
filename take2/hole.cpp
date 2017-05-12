#include "hole.h"



hole::hole(float posX, float posY, int size, sf::Color colour, b2World * world, Conversion &convert)
{
	m_world = world;
	m_convert = &convert;
	m_colour = colour;

	float length = m_convert->scaleNumber(size);

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(m_convert->canvasXToBox2D(posX), m_convert->canvasYToBox2D(posY));
	m_b2body = world->CreateBody(&m_bodyDef);

	m_b2Shape1.SetAsBox(length / 6, length / 4, b2Vec2(0 - length / 3, 0), 0);
	m_b2Fix1.shape = &m_b2Shape1;
	m_b2Fix1.density = 1;
	m_b2Fix1.friction = 1;
	m_b2Fix1.restitution = 0;
	m_b2body->CreateFixture(&m_b2Fix1);

	m_b2Shape2.SetAsBox(length / 6, length / 40 , b2Vec2(0, length / 40 - (length / 4)), 0);
	m_b2Fix2.shape = &m_b2Shape2;
	m_b2Fix2.density = 1;
	m_b2Fix2.friction = 1;
	m_b2Fix2.restitution = 0;
	m_b2body->CreateFixture(&m_b2Fix2);

	m_b2Shape3.SetAsBox(length / 6, length / 4 , b2Vec2(length / 3, 0), 0);
	m_b2Fix3.shape = &m_b2Shape3;
	m_b2Fix3.density = 1;
	m_b2Fix3.friction = 1;
	m_b2Fix3.restitution = 0;
	m_b2body->CreateFixture(&m_b2Fix3);


	//set up sf rectangle over the top of the 3 b2Shapes
	m_sfRectShape.setSize(sf::Vector2f(size, size / 2));
	m_sfRectShape.setPosition(posX, posY);
	m_sfRectShape.setFillColor(m_colour);
	m_sfRectShape.setOrigin(size / 2, size / 4);

	if (!m_flagTexture.loadFromFile("../resources/flag.png"))
	{
		std::cout << "Could not load flag.png" << std::endl;
	}
	m_flag.setTexture(m_flagTexture);
	m_flag.setOrigin(m_flagTexture.getSize().x / 2, m_flagTexture.getSize().y);
	m_flag.setPosition(m_sfRectShape.getPosition().x, m_sfRectShape.getPosition().y + m_sfRectShape.getSize().y / 2);
	m_flag.setScale(0.2, 0.2);
}

void hole::Update()
{
	m_sfRectShape.setPosition(
		m_convert->box2DXToCanvas(m_b2body->GetPosition().x), 
		m_convert->box2DYToCanvas(m_b2body->GetPosition().y)
	);
}

bool hole::IsWinCondition(MyShape * shape)
{
	if (shape->isMoving() != true && m_sfRectShape.getGlobalBounds().contains(
		m_convert->box2DXToCanvas(shape->GetBodyPosition().x), 
		m_convert->box2DYToCanvas(shape->GetBodyPosition().y))
		)
		return true;
	return false;
}

b2Body * hole::GetBody()
{
	return m_b2body;
}

b2Vec2 hole::GetPosition()
{
	return m_b2body->GetPosition();
}

void hole::Draw(sf::RenderWindow &window)
{
	window.draw(m_sfRectShape);
	window.draw(m_flag);
}

hole::~hole()
{
}
