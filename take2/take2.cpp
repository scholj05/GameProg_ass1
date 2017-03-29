#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>

#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Conversion.h"
#include "physics.h"

//	Main class runs the game loop and handles events/inputs.
//
//	Physics class creates shapes based on a position,
//	bodytype and number of vertices(angularly symmetrical).
//
//	Conversion class converts SFML world coordinates and degrees 
//	to Box2D world coordinates and radians.

bool m_debug = false;

float scale = 0.01;
float crateWidth = 20;

float scaledWidth;
float scaledHeight;

int points = 3;

int main()
{
	Shape shape(m_debug);

	///Box2D value declaration
	b2Vec2 gravity(0.0f, -9.8f);///define gravity
	float TIMESTEP = 1.0f / 96.0f;///step per frame @ 60FPS
	int VELOCITY = 4;///iterations of velocity update per step
	int POSITION = 10;///iterations of position update per step
	b2World * world = new b2World(gravity);///define world
	world->SetAllowSleeping(false);///don't allow objects in box2D world to pause

								   ///SFML window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Take 2: more successful than take 1");
	window.setFramerateLimit(96); /// control how fast the screen is refreshed (fps)


	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Could not load arial.ttf font" << std::endl;
	}
	sf::Clock clock;
	float lastTime = 0;
	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(10);
	fpsText.setColor(sf::Color::White);
	fpsText.setPosition(12, 0);


	///setup conversion class
	scaledWidth = scale * (window.getSize().x);
	scaledHeight = scale * (window.getSize().y);
	Conversion convert(scale, scaledWidth, scaledHeight);

	std::list<b2Body*> graveyard; ///list of bodies to be destroyed at next delete phase

								  ///Borders
	b2PolygonShape leftWall;
	leftWall = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(5), convert.canvasYToBox2D(362.5)), scale * 10, scale * 725);
	b2FixtureDef leftWallFixture = shape.setFixture(1, 1, 0);
	leftWallFixture.shape = &leftWall;
	b2BodyDef wallBodyDef;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	b2Body * wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&leftWallFixture);

	b2PolygonShape leftRamp;
	b2Vec2 leftRampArray[] =
	{
		b2Vec2(convert.canvasXToBox2D(0), convert.canvasYToBox2D(725)),
		b2Vec2(convert.canvasXToBox2D(10), convert.canvasYToBox2D(725)),
		b2Vec2(convert.canvasXToBox2D(250), convert.canvasYToBox2D(925)),
		b2Vec2(convert.canvasXToBox2D(0), convert.canvasYToBox2D(925)),
	};
	leftRamp.Set(leftRampArray, 4);
	b2FixtureDef leftRampFixture = shape.setFixture(1, 0.5, 0);
	leftRampFixture.shape = &leftRamp;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&leftRampFixture);

	b2PolygonShape leftGround;
	leftGround = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(200), convert.canvasYToBox2D(995)), scale * 400, scale * 10);
	b2FixtureDef leftGroundFixture = shape.setFixture(1, 1, 0);
	leftGroundFixture.shape = &leftGround;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&leftGroundFixture);

	b2PolygonShape RightWall;
	RightWall = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(995), convert.canvasYToBox2D(362.5)), scale * 10, scale * 725);
	b2FixtureDef RightWallFixture = shape.setFixture(1, 1, 0);
	RightWallFixture.shape = &RightWall;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&RightWallFixture);

	b2PolygonShape rightRamp;
	b2Vec2 rightRampArray[] =
	{
		b2Vec2(convert.canvasXToBox2D(990), convert.canvasYToBox2D(725)),
		b2Vec2(convert.canvasXToBox2D(1000), convert.canvasYToBox2D(725)),
		b2Vec2(convert.canvasXToBox2D(1000), convert.canvasYToBox2D(925)),
		b2Vec2(convert.canvasXToBox2D(750), convert.canvasYToBox2D(925)),
	};
	rightRamp.Set(rightRampArray, 4);
	b2FixtureDef rightRampFixture = shape.setFixture(1, 0.5, 0);
	rightRampFixture.shape = &rightRamp;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&rightRampFixture);

	b2PolygonShape rightGround;
	rightGround = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(800), convert.canvasYToBox2D(995)), scale * 400, scale * 10);
	b2FixtureDef rightGroundFixture = shape.setFixture(1, 1, 0);
	rightGroundFixture.shape = &rightGround;
	wallBodyDef.type = b2BodyType::b2_staticBody;
	wallBody = world->CreateBody(&wallBodyDef);
	wallBody->CreateFixture(&rightGroundFixture);

	///pushers
	b2PolygonShape leftPusher;
	leftPusher = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(100), convert.canvasYToBox2D(957.5)), scale * 400, scale * 65);
	b2FixtureDef leftPusherFixture = shape.setFixture(1, 1, 0);
	leftPusherFixture.shape = &leftPusher;
	b2BodyDef leftPusherBodyDef;
	leftPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	b2Body * leftPusherBody = world->CreateBody(&leftPusherBodyDef);
	leftPusherBody->CreateFixture(&leftPusherFixture);
	bool leftPusherMoveLeft = true;

	b2PolygonShape rightPusher;
	rightPusher = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(900), convert.canvasYToBox2D(957.5)), scale * 400, scale * 65);
	b2FixtureDef rightPusherFixture = shape.setFixture(1, 1, 0);
	rightPusherFixture.shape = &rightPusher;
	b2BodyDef rightPusherBodyDef;
	rightPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	b2Body * rightPusherBody = world->CreateBody(&rightPusherBodyDef);
	rightPusherBody->CreateFixture(&rightPusherFixture);
	bool rightPusherMoveRight = true;

	///spinner
	b2PolygonShape windmillH;
	windmillH = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(500), convert.canvasYToBox2D(500)), scale * 300, scale * 5);
	b2FixtureDef windmillHFixture = shape.setFixture(1, 1, 0);
	windmillHFixture.shape = &windmillH;
	b2BodyDef windmillBodyDef;
	leftPusherBodyDef.type = b2BodyType::b2_kinematicBody;
	b2Body * windmillBody = world->CreateBody(&windmillBodyDef);
	windmillBody->CreateFixture(&windmillHFixture);


	b2PolygonShape windmillV;
	windmillV = shape.calculateRectangle(b2Vec2(convert.canvasXToBox2D(500), convert.canvasYToBox2D(500)), scale * 5, scale * 300);
	b2FixtureDef windmillVFixture = shape.setFixture(1, 1, 0);
	windmillVFixture.shape = &windmillV;
	windmillBodyDef.type = b2BodyType::b2_kinematicBody;
	windmillBody = world->CreateBody(&windmillBodyDef);
	windmillBody->CreateFixture(&windmillVFixture);

	windmillBody->SetFixedRotation(true);
	windmillBody->SetAngularVelocity(-1);

	///Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					b2Vec2 mouse = b2Vec2(convert.canvasXToBox2D(sf::Mouse::getPosition(window).x), convert.canvasYToBox2D(sf::Mouse::getPosition(window).y));
					b2PolygonShape particle;
					particle = shape.calculateRandomShape(mouse);

					b2FixtureDef particleFixture = shape.setFixture(1, 0.3, 0.5);
					particleFixture.shape = &particle;

					b2BodyDef particleBodyDef;
					particleBodyDef.type = b2BodyType::b2_dynamicBody;

					b2Body * particleBody = world->CreateBody(&particleBodyDef);
					particleBody->CreateFixture(&particleFixture);

					sf::Color colour = sf::Color(convert.getRandomInt(0, 255), convert.getRandomInt(0, 255), convert.getRandomInt(0, 255));
					particleBody->SetUserData(&colour);
				}

				if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
				{
					b2Vec2 mouse = b2Vec2(convert.canvasXToBox2D(sf::Mouse::getPosition(window).x), convert.canvasYToBox2D(sf::Mouse::getPosition(window).y));
					b2PolygonShape particle;
					particle = shape.calculateRandomShape(mouse);

					b2FixtureDef particleFixture = shape.setFixture(1, 0.3, 0.5);
					particleFixture.shape = &particle;

					b2BodyDef particleBodyDef;
					particleBodyDef.type = b2BodyType::b2_staticBody;

					b2Body * particleBody = world->CreateBody(&particleBodyDef);
					particleBody->CreateFixture(&particleFixture);

					sf::Color colour = sf::Color(convert.getRandomInt(0, 255), convert.getRandomInt(0, 255), convert.getRandomInt(0, 255));
					particleBody->SetUserData(&colour);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					m_debug = !m_debug;
					shape.setDebug(m_debug);
				}
			}
		}
		window.clear();

		///update kinematic objects
		b2Vec2 leftPusherPosition = leftPusherBody->GetPosition();
		//std::cout << "leftPusherPosition.x: " << convert.box2DXToCanvas(leftPusherPosition.x) << std::endl << "moveLeft: " << leftPusherMoveLeft << std::endl;
		if (leftPusherPosition.x <= convert.canvasXToBox2D(449))
			leftPusherMoveLeft = false;
		else if (leftPusherPosition.x >= convert.canvasXToBox2D(600))
			leftPusherMoveLeft = true;

		if (leftPusherMoveLeft == true)
			leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x - scale * 2, leftPusherPosition.y), 0);
		else
			leftPusherBody->SetTransform(b2Vec2(leftPusherPosition.x + scale * 2, leftPusherPosition.y), 0);

		b2Vec2 rightPusherPosition = rightPusherBody->GetPosition();
		if (rightPusherPosition.x >= convert.canvasXToBox2D(551))
			rightPusherMoveRight = false;
		else if (rightPusherPosition.x <= convert.canvasXToBox2D(400))
			rightPusherMoveRight = true;

		if (rightPusherMoveRight)
			rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x + scale * 2, rightPusherPosition.y), 0);
		else
			rightPusherBody->SetTransform(b2Vec2(rightPusherPosition.x - scale * 2, rightPusherPosition.y), 0);



		world->Step(TIMESTEP, VELOCITY, POSITION);

		///clear bodies scheduled for deletion
		for (std::list<b2Body*>::iterator it = graveyard.begin(); it != graveyard.end(); ++it)
		{
			(*it)->GetWorld()->DestroyBody(*it);
		}
		graveyard.clear();

		b2Body *body = world->GetBodyList();
		while (body != NULL)
		{
			b2Vec2 position = body->GetPosition();
			b2Fixture *fixture = body->GetFixtureList();

			while (fixture != NULL)
			{
				switch (fixture->GetType())
				{
				case b2Shape::e_polygon:
				{
					b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

					if (body->GetType() == b2BodyType::b2_dynamicBody) // draw shape using a sprite
					{
						if (convert.box2DYToCanvas(body->GetPosition().y) > 2000)
						{
							//body->GetWorld()->DestroyBody(body);/// wrong time to delete
							graveyard.push_back(body);
						}
						else
						{
							sf::ConvexShape dynamic;
							dynamic.setOutlineColor(sf::Color::White);
							sf::Color * tempColour = new sf::Color;
							tempColour = (sf::Color*)body->GetUserData();
							dynamic.setFillColor(*tempColour);
							dynamic.setOutlineThickness(1.0f);
							dynamic.setPointCount(poly->GetVertexCount());

							for (int32 i = 0; i < poly->GetVertexCount(); i++)
							{
								const b2Vec2 src = poly->GetVertex(i); // local vertex around 0,0
								const b2Vec2 world = body->GetWorldPoint(src); // convert to a global world point

								float x = convert.box2DXToCanvas(world.x);
								float y = convert.box2DYToCanvas(world.y);

								dynamic.setPoint(i, sf::Vector2f(x, y));
							}
							window.draw(dynamic);
						}


					}
					else // draw shape using a vertexes
					{
						sf::ConvexShape convex;
						convex.setOutlineColor(sf::Color::White);
						convex.setFillColor(sf::Color::Green);
						convex.setOutlineThickness(1.0f);
						convex.setPointCount(poly->GetVertexCount());

						for (int32 i = 0; i < poly->GetVertexCount(); i++)
						{
							const b2Vec2 src = poly->GetVertex(i); // local vertex around 0,0
							const b2Vec2 world = body->GetWorldPoint(src); // convert to a global world point

							float x = convert.box2DXToCanvas(world.x);
							float y = convert.box2DYToCanvas(world.y);

							convex.setPoint(i, sf::Vector2f(x, y));
						}
						window.draw(convex);
					}
				}
				break;
				}
				fixture = fixture->GetNext();
			}
			body = body->GetNext();
		}
		float currentTime = clock.restart().asSeconds();
		int fps = 1.f / currentTime;
		std::ostringstream buff;
		buff << fps;
		fpsText.setString((sf::String(buff.str())));
		window.draw(fpsText);

		window.display();
	}

	return 0;
}