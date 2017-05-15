#include "Level.h"



void Level::Level1(b2World * world, Conversion * convert, CreateShape * shape, float boundaryX, float boundaryY)
{
	m_convert = convert;
	
	/// Boundary Walls
	CreateWalls(world, boundaryX, boundaryY);


	///pushers
	leftPusher = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(400), convert->scaleNumber(20));
	b2FixtureDef leftPusherFixture = shape->setFixture(1, 1, 0);
	leftPusherFixture.shape = &leftPusher;
	b2BodyDef leftPusherBodyDef;
	leftPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	leftPusherBodyDef.position.Set(convert->canvasXToBox2D(1600), convert->canvasYToBox2D(1970));
	leftPusherBody = world->CreateBody(&leftPusherBodyDef);
	leftPusherBody->CreateFixture(&leftPusherFixture);
	leftPusherMoveLeft = true;
	kinematicList.push_back(leftPusherBody);

	rightPusher = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(20), convert->scaleNumber(400));
	b2FixtureDef rightPusherFixture = shape->setFixture(1, 1, 0);
	rightPusherFixture.shape = &rightPusher;
	b2BodyDef rightPusherBodyDef;
	rightPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	rightPusherBodyDef.position.Set(convert->canvasXToBox2D(400), convert->canvasYToBox2D(1960));
	rightPusherBody = world->CreateBody(&rightPusherBodyDef);
	rightPusherBody->CreateFixture(&rightPusherFixture);
	rightPusherMoveRight = true;
	kinematicList.push_back(rightPusherBody);

	///spinner
	windmillH = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(500), convert->scaleNumber(10));
	windmillV = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(10), convert->scaleNumber(500));
	b2FixtureDef windmillHFixture = shape->setFixture(1, 1, 0), windmillVFixture = shape->setFixture(1, 1, 0);
	windmillHFixture.shape = &windmillH;
	windmillVFixture.shape = &windmillV;

	b2BodyDef windmillBodyDef;
	windmillBodyDef.type = b2BodyType::b2_kinematicBody;
	windmillBodyDef.position.Set(convert->canvasXToBox2D(1000), convert->canvasYToBox2D(1725));
	windmillBody = world->CreateBody(&windmillBodyDef);
	windmillBody->CreateFixture(&windmillHFixture);
	windmillBody->CreateFixture(&windmillVFixture);
	windmillBody->SetFixedRotation(true);
	windmillBody->SetAngularVelocity(-0.5);
	kinematicList.push_back(windmillBody);
}

void Level::CreateWalls(b2World *world, float boundaryX, float boundaryY)
{
	level1WorldBoundary = sf::FloatRect(0.0f, 0.0f, boundaryX, boundaryY);
	int borderThickness = 25;

	topWall = m_shape->calculateRectangle(b2Vec2(m_convert->canvasXToBox2D(level1WorldBoundary.width / 2), m_convert->canvasYToBox2D(borderThickness / 2)), m_convert->scaleNumber(level1WorldBoundary.width), m_convert->scaleNumber(borderThickness));
	b2FixtureDef topWallFixture = m_shape->setFixture(1, 1, 0);
	topWallFixture.shape = &topWall;
	b2BodyDef wallBodyDef;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&topWallFixture);
	

	leftWall = m_shape->calculateRectangle(
		b2Vec2(m_convert->canvasXToBox2D(borderThickness / 2), 
			m_convert->canvasYToBox2D(level1WorldBoundary.height / 2)), 
			m_convert->scaleNumber(borderThickness), 
			m_convert->scaleNumber(level1WorldBoundary.height));
	b2FixtureDef leftWallFixture = m_shape->setFixture(1, 1, 0);
	leftWallFixture.shape = &leftWall;
	wallBody->CreateFixture(&leftWallFixture);

	bottomWall = m_shape->calculateRectangle(
		b2Vec2(m_convert->canvasXToBox2D(level1WorldBoundary.width / 2), 
			m_convert->canvasYToBox2D(level1WorldBoundary.height - (borderThickness / 2))),
			m_convert->scaleNumber(level1WorldBoundary.width), 
			m_convert->scaleNumber(borderThickness));
	b2FixtureDef bottomWallFixture = m_shape->setFixture(1, 1, 0);
	bottomWallFixture.shape = &bottomWall;
	wallBody->CreateFixture(&bottomWallFixture);

	rightWall = m_shape->calculateRectangle(
		b2Vec2(m_convert->canvasXToBox2D(level1WorldBoundary.width - (borderThickness / 2)), 
			m_convert->canvasYToBox2D(level1WorldBoundary.height / 2)), 
			m_convert->scaleNumber(borderThickness), 
			m_convert->scaleNumber(level1WorldBoundary.height));
	b2FixtureDef rightWallFixture = m_shape->setFixture(1, 1, 0);
	rightWallFixture.shape = &rightWall;
	wallBody->CreateFixture(&rightWallFixture);

}

void Level::UpdateKinematicObjects()
{
	///update kinematic objects
	b2Vec2 rightPusherPosition = rightPusherBody->GetPosition();

	if (rightPusherPosition.y <= m_convert->canvasXToBox2D(1200))
		rightPusherMoveRight = false;
	else if (rightPusherPosition.y >= m_convert->canvasXToBox2D(1775))
		rightPusherMoveRight = true;

	if (rightPusherMoveRight == true)
		rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x, rightPusherPosition.y - m_convert->scaleNumber(5)), 0);
	else
		rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x, rightPusherPosition.y + m_convert->scaleNumber(5)), 0);


	b2Vec2 leftPusherPosition = leftPusherBody->GetPosition();

	if (leftPusherPosition.x >= m_convert->canvasXToBox2D(1775))
		leftPusherMoveLeft = false;
	else if (leftPusherPosition.x <= m_convert->canvasXToBox2D(1500))
		leftPusherMoveLeft = true;

	if (leftPusherMoveLeft)
		leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x + m_convert->scaleNumber(2), leftPusherPosition.y), 0);
	else
		leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x - m_convert->scaleNumber(2), leftPusherPosition.y), 0);
}

b2Body * Level::GetWall()
{
	return wallBody;
}

std::list<b2Body*> Level::GetStaticList()
{
	return staticList;
}

void Level::PushStaticList(b2Body * body)
{
	staticList.push_back(body);
}

std::list<b2Body*> Level::GetKinematicList()
{
	return kinematicList;
}

void Level::PushKinematicList(b2Body * body)
{
	kinematicList.push_back(body);
}

void Level::Cleanup()
{
	for (std::list<b2Body*>::iterator it = graveyard.begin(); it != graveyard.end(); ++it)
	{
		(*it)->GetWorld()->DestroyBody(*it);
	}
	graveyard.clear();
}

void Level::Destroy(b2Body * body)
{
	graveyard.push_back(body);
}

void Level::ClearWorld()
{
	while (staticList.size() > 0)
	{
		Destroy(staticList.front());
		staticList.pop_front();
	}
}
