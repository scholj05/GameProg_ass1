#include "Level.h"



void Level::Level1(b2World * world, Conversion * convert, CreateShape * shape, float boundaryX, float boundaryY)
{
	m_convert = convert;
	level1WorldBoundary = sf::FloatRect(0.0f, 0.0f, boundaryX, boundaryY);
	int borderThickness = 10;
	
	// Boundary Walls
	topWall = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(level1WorldBoundary.width / 2), convert->canvasYToBox2D(borderThickness / 2)), convert->scaleNumber(level1WorldBoundary.width), convert->scaleNumber(borderThickness));
	b2FixtureDef topWallFixture = shape->setFixture(1, 1, 0);
	topWallFixture.shape = &topWall;
	b2BodyDef wallBodyDef;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&topWallFixture);
	
	leftWall = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(borderThickness / 2), convert->canvasYToBox2D(level1WorldBoundary.height / 2)), convert->scaleNumber(borderThickness), convert->scaleNumber(level1WorldBoundary.height));
	b2FixtureDef leftWallFixture = shape->setFixture(1, 1, 0);
	leftWallFixture.shape = &leftWall;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&leftWallFixture);
	
	bottomWall = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(level1WorldBoundary.width / 2), convert->canvasYToBox2D(level1WorldBoundary.height - (borderThickness / 2))), convert->scaleNumber(level1WorldBoundary.width), convert->scaleNumber(borderThickness));
	b2FixtureDef bottomWallFixture = shape->setFixture(1, 1, 0);
	bottomWallFixture.shape = &bottomWall;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&bottomWallFixture);

	rightWall = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(level1WorldBoundary.width - (borderThickness / 2)), convert->canvasYToBox2D(level1WorldBoundary.height / 2)), convert->scaleNumber(borderThickness), convert->scaleNumber(level1WorldBoundary.height));
	b2FixtureDef rightWallFixture = shape->setFixture(1, 1, 0);
	rightWallFixture.shape = &rightWall;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&rightWallFixture);
	
	/*
	b2PolygonShape leftRamp;
	b2Vec2 leftRampArray[] =
	{
	b2Vec2(convert->canvasXToBox2D(0), convert->canvasYToBox2D(725)),
	b2Vec2(convert->canvasXToBox2D(10), convert->canvasYToBox2D(725)),
	b2Vec2(convert->canvasXToBox2D(250), convert->canvasYToBox2D(925)),
	b2Vec2(convert->canvasXToBox2D(0), convert->canvasYToBox2D(925)),
	};
	leftRamp.Set(leftRampArray, 4);
	b2FixtureDef leftRampFixture = shape.setFixture(1, 0.5, 0);
	leftRampFixture.shape = &leftRamp;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&leftRampFixture);
	b2PolygonShape rightRamp;
	b2Vec2 rightRampArray[] =
	{
	b2Vec2(convert->canvasXToBox2D(990), convert->canvasYToBox2D(725)),
	b2Vec2(convert->canvasXToBox2D(1000), convert->canvasYToBox2D(725)),
	b2Vec2(convert->canvasXToBox2D(1000), convert->canvasYToBox2D(925)),
	b2Vec2(convert->canvasXToBox2D(750), convert->canvasYToBox2D(925)),
	};
	rightRamp.Set(rightRampArray, 4);
	b2FixtureDef rightRampFixture = shape.setFixture(1, 0.5, 0);
	rightRampFixture.shape = &rightRamp;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&rightRampFixture);

	*/


	///pushers
	leftPusher = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(100), convert->canvasYToBox2D(957.5)), convert->scaleNumber(400), convert->scaleNumber(65));
	b2FixtureDef leftPusherFixture = shape->setFixture(1, 1, 0);
	leftPusherFixture.shape = &leftPusher;
	b2BodyDef leftPusherBodyDef;
	leftPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	leftPusherBody = world->CreateBody(&leftPusherBodyDef);
	leftPusherBody->CreateFixture(&leftPusherFixture);
	leftPusherMoveLeft = true;

	rightPusher = shape->calculateRectangle(b2Vec2(convert->canvasXToBox2D(900), convert->canvasYToBox2D(957.5)), convert->scaleNumber(400), convert->scaleNumber(65));
	b2FixtureDef rightPusherFixture = shape->setFixture(1, 1, 0);
	rightPusherFixture.shape = &rightPusher;
	b2BodyDef rightPusherBodyDef;
	rightPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	rightPusherBody = world->CreateBody(&rightPusherBodyDef);
	rightPusherBody->CreateFixture(&rightPusherFixture);
	rightPusherMoveRight = true;

	///spinner
	windmillH = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(300), convert->scaleNumber(5));
	windmillV = shape->calculateRectangle(b2Vec2(0, 0), convert->scaleNumber(5), convert->scaleNumber(300));
	b2FixtureDef windmillHFixture = shape->setFixture(1, 1, 0), windmillVFixture = shape->setFixture(1, 1, 0);
	windmillHFixture.shape = &windmillH;
	windmillVFixture.shape = &windmillV;

	b2BodyDef windmillBodyDef;
	windmillBodyDef.type = b2BodyType::b2_kinematicBody;
	windmillBodyDef.position.Set(convert->canvasXToBox2D(500), convert->canvasYToBox2D(500));
	windmillBody = world->CreateBody(&windmillBodyDef);
	windmillBody->CreateFixture(&windmillHFixture);
	windmillBody->CreateFixture(&windmillVFixture);

	windmillBody->SetFixedRotation(true);
	windmillBody->SetAngularVelocity(-0.5);
}

void Level::updateKinematicObjects()
{
	///update kinematic objects
	b2Vec2 leftPusherPosition = leftPusherBody->GetPosition();
	//std::cout << "leftPusherPosition.x: " << convert.box2DXToCanvas(leftPusherPosition.x) << std::endl << "moveLeft: " << leftPusherMoveLeft << std::endl;
	//std::cout << "windmill center: " << windmillBody->GetPosition().x << ", " << windmillBody->GetPosition().y << std::endl;
	if (leftPusherPosition.x <= m_convert->canvasXToBox2D(449))
		leftPusherMoveLeft = false;
	else if (leftPusherPosition.x >= m_convert->canvasXToBox2D(600))
		leftPusherMoveLeft = true;

	if (leftPusherMoveLeft == true)
		leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x - m_convert->scaleNumber(2), leftPusherPosition.y), 0);
	else
		leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x + m_convert->scaleNumber(2), leftPusherPosition.y), 0);


	b2Vec2 rightPusherPosition = rightPusherBody->GetPosition();
	if (rightPusherPosition.x >= m_convert->canvasXToBox2D(551))
		rightPusherMoveRight = false;
	else if (rightPusherPosition.x <= m_convert->canvasXToBox2D(400))
		rightPusherMoveRight = true;

	if (rightPusherMoveRight)
		rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x + m_convert->scaleNumber(2), rightPusherPosition.y), 0);
	else
		rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x - m_convert->scaleNumber(2), rightPusherPosition.y), 0);
}
