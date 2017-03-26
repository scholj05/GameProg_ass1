<<<<<<< HEAD
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

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


float scale = 0.01;
float crateWidth = 20;

float scaledWidth;
float scaledHeight;

int points = 3;

int main()
{
	Shape shape;

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(crateWidth, crateWidth));
	rect.setOrigin(10, 10);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Blue);

	//Box2D value declaration
	b2Vec2 gravity(0.0f, -9.8f);//define gravity
	float TIMESTEP = 1.0f / 60.0f;//step per frame @ 60FPS
	int VELOCITY = 4;//iterations of velocity update per step
	int POSITION = 2;//iterations of position update per step
	b2World * world = new b2World(gravity);//define world
	world->SetAllowSleeping(false);//don't allow objects in box2D world to pause

	//SFML window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Take 2: more successful than take 1");
	window.setFramerateLimit(60); // control how fast the screen is refreshed (fps)

	//setup conversion class
	scaledWidth = scale * (window.getSize().x);
	scaledHeight = scale * (window.getSize().y);
	Conversion convert(scale, scaledWidth, scaledHeight);
	
	//Borders
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

	//pushers
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
					sf::Vector2i mouse = sf::Mouse::getPosition(window);

					// define our dynamic body
					b2BodyDef crate;
					crate.type = b2BodyType::b2_dynamicBody;
					// capture the position of the mouse in world co-ordinates using our convertor methods
					crate.position.Set(convert.canvasXToBox2D(mouse.x), convert.canvasYToBox2D(mouse.y));

					// define the shape of our dynamic body
					b2PolygonShape crateShape;
					crateShape.SetAsBox((crateWidth * scale) / 2.0f, (crateWidth * scale) / 2.0f);

					// define the physical properties of our shape
					b2FixtureDef crateFd;
					crateFd.shape = &crateShape;
					crateFd.density = 1.0f;
					crateFd.friction = 0.3f;
					crateFd.restitution = 0.2f;

					b2Body *crateBody = world->CreateBody(&crate); // allocate the object to the game world
					crateBody->CreateFixture(&crateFd); // attach the fixture properties to our object

					bool test = false; // example data attachment
					crateBody->SetUserData(&test); // attach some data; does not do anything currently!
				}
			}
		}
		window.clear();

		///update kinematic objects
		b2Vec2 leftPusherPosition = leftPusherBody->GetPosition();
		std::cout << "leftPusherPosition.x: " << convert.box2DXToCanvas(leftPusherPosition.x) << std::endl << "moveLeft: " << leftPusherMoveLeft << std::endl;
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
						rect.setRotation(convert.radiansToDegrees(body->GetAngle()));

						float x = convert.box2DXToCanvas(position.x);
						float y = convert.box2DYToCanvas(position.y);

						rect.setPosition(x, y);
						window.draw(rect);

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

		window.display();
	}

	return 0;
}
=======
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Conversion.h"

//	Main class runs the game loop and handles events/inputs.
//
//	Physics class creates shapes based on a position,
//	bodytype and number of vertices(angularly symmetrical).
//
//	Conversion class converts SFML world coordinates and degrees 
//	to Box2D world coordinates and radians.


float scale = 0.01;
float crateWidth = 20;

float scaledWidth;
float scaledHeight;

//repo test

int main()
{
	sf::Texture texture;
	texture.loadFromFile("assets/crate.jpg");

	sf::Sprite sprite(texture);
	sprite.setOrigin(10, 10);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(crateWidth, crateWidth));
	rect.setOrigin(10, 10);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Blue);

	//Box2D value declaration
	b2Vec2 gravity(0.0f, -9.8f);//define gravity
	float TIMESTEP = 1.0f / 60.0f;//step per frame @ 60FPS
	int VELOCITY = 4;//iterations of velocity update per step
	int POSITION = 2;//iterations of position update per step
	b2World world = b2World(gravity);//define world
	world.SetAllowSleeping(false);//don't allow objects in box2D world to pause

	//SFML window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Box2D Example");

	//setup conversion class
	scaledWidth = scale * (window.getSize().x);
	scaledHeight = scale * (window.getSize().y);
	Conversion convert(scale, scaledWidth, scaledHeight);
	
	

	//// code to create out ground box
	//b2PolygonShape groundBox;
	//
	//groundBox.SetAsBox(scaledWidth / 2.0f /* half width */, 0.1f /* half height */);

	//b2FixtureDef groundFixture;
	//groundFixture.shape = &groundBox;
	//groundFixture.density = 1.0f;
	//groundFixture.friction = 0.4f;

	//b2BodyDef bd;
	//bd.type = b2BodyType::b2_staticBody;
	//bd.position.Set(0.0f, -(scaledHeight/2.0f)); // with respect to the center of mass of our polygon shape

	//b2Body *body = world.CreateBody(&bd);
	//body->CreateFixture(&groundFixture);

	b2PolygonShape poly1;
	b2Vec2 shape1[] = { b2Vec2(-0.25,-2.3),
		b2Vec2(-1,-1.95),
		b2Vec2(-2,-1.65),
		b2Vec2(-3,-2.41),
		b2Vec2(-3,-3.75),
		b2Vec2(-0.25,-3.75),
		b2Vec2(-0.25,-2.3),
	};
	poly1.Set(shape1, 7);

	b2FixtureDef poly1Fixture;
	poly1Fixture.shape = &poly1;
	poly1Fixture.density = 1.0f;
	poly1Fixture.friction = 0.4f;

	b2BodyDef poly1Def;
	poly1Def.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	b2Body *poly1Body = world.CreateBody(&poly1Def);
	poly1Body->CreateFixture(&poly1Fixture);

	b2PolygonShape poly2;
	b2Vec2 shape2[] = { b2Vec2(0.36,-1.45),
		b2Vec2(0.27,-1.45),
		b2Vec2(0.0899999999999999,-1.75),
		b2Vec2(-0.02,-2.05),
		b2Vec2(-0.25,-2.3),
		b2Vec2(-0.25,-3.75),
		b2Vec2(0.36,-3.75),
		b2Vec2(0.36,-1.45)
	};
	poly2.Set(shape2, 8);

	b2FixtureDef poly2Fixture;
	poly2Fixture.shape = &poly2;
	poly2Fixture.density = 1.0f;
	poly2Fixture.friction = 0.4f;

	b2BodyDef poly2Def;
	poly2Def.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	b2Body *poly2Body = world.CreateBody(&poly2Def);
	poly2Body->CreateFixture(&poly2Fixture);

	b2PolygonShape poly3;
	b2Vec2 shape3[] = { b2Vec2(1.62,-2.65),
		b2Vec2(1.2,-2.05),
		b2Vec2(0.36,-1.45),
		b2Vec2(0.36,-3.75),
		b2Vec2(1.62,-3.75),
		b2Vec2(1.62,-2.65)



	};
	poly3.Set(shape3, 6);

	b2FixtureDef poly3Fixture;
	poly3Fixture.shape = &poly3;
	poly3Fixture.density = 1.0f;
	poly3Fixture.friction = 0.4f;

	b2BodyDef poly3Def;
	poly3Def.type = b2BodyType::b2_staticBody;

	b2Body *poly3Body = world.CreateBody(&poly3Def);
	poly3Body->CreateFixture(&poly3Fixture);

	b2PolygonShape poly4;
	b2Vec2 shape4[] = { b2Vec2(3,-3.75),
		b2Vec2(3,-1.06),
		b2Vec2(2.27,-1.06),
		b2Vec2(1.98,-1.29),
		b2Vec2(1.76,-1.6),
		b2Vec2(1.62,-2.48),
		b2Vec2(1.62,-3.75)


	};
	poly4.Set(shape4, 7);

	b2FixtureDef poly4Fixture;
	poly4Fixture.shape = &poly4;
	poly4Fixture.density = 1.0f;
	poly4Fixture.friction = 0.4f;

	b2BodyDef poly4Def;
	poly4Def.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	b2Body *poly4Body = world.CreateBody(&poly4Def);
	poly4Body->CreateFixture(&poly4Fixture);

	b2PolygonShape triangleShape;
	b2Vec2 triangle[] = { b2Vec2(0.5,1.0),
		b2Vec2(0.0f, 0.0f),
		b2Vec2(1.0,0.0)
	};
	triangleShape.Set(triangle, 3);

	b2FixtureDef triangleFixture;
	triangleFixture.shape = &triangleShape;
	triangleFixture.density = 1.0f;
	triangleFixture.friction = 0.4f;

	b2BodyDef triangleDef;
	triangleDef.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	b2Body *triangleBody = world.CreateBody(&triangleDef);
	poly4Body->CreateFixture(&triangleFixture);

	b2PolygonShape rectangleShape;
	b2Vec2 rectangle[] = { b2Vec2(-1,2.75),
		b2Vec2(-2,2.75),
		b2Vec2(-2,1.75),
		b2Vec2(-1,1.75)
	};
	rectangleShape.Set(rectangle, 4);

	b2FixtureDef rectangleFixture;
	rectangleFixture.shape = &rectangleShape;
	rectangleFixture.density = 1.0f;
	rectangleFixture.friction = 0.4f;

	b2BodyDef rectangleDef;
	rectangleDef.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	b2Body *rectangleBody = world.CreateBody(&rectangleDef);
	poly4Body->CreateFixture(&rectangleFixture);

	b2PolygonShape octagonShape;
	b2Vec2 octagon[] = { b2Vec2(-0.4677255,1.8155174),
		b2Vec2(-0.4788614,2.4024017),
		b2Vec2(-0.9017255,2.80951724),
		b2Vec2(-1.4886098,2.79838134),
		b2Vec2(-1.8957254,2.3755172),
		b2Vec2(-1.8845895,1.7886329),
		b2Vec2(-1.4617254,1.3815173),
		b2Vec2(-0.8748411,1.3926532)

	};
	octagonShape.Set(octagon, 8);

	b2FixtureDef octagonFixture;
	octagonFixture.shape = &octagonShape;
	octagonFixture.density = 1.0f;
	octagonFixture.friction = 0.4f;

	b2BodyDef octagonDef;
	octagonDef.type = b2BodyType::b2_staticBody;
	// poly1Def.position.Set(0, 0); // with respect to the center of mass of our polygon shape

	//b2Body *octagonBody = world.CreateBody(&octagonDef);
	//poly4Body->CreateFixture(&octagonFixture);


	window.setFramerateLimit(60); // control how fast the screen is refreshed (fps)

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
					sf::Vector2i mouse = sf::Mouse::getPosition(window);

					// define our dynamic body
					b2BodyDef crate;
					crate.type = b2BodyType::b2_dynamicBody;
					// capture the position of the mouse in world co-ordinates using our convertor methods
					crate.position.Set(convert.canvasXToBox2D(mouse.x), convert.canvasYToBox2D(mouse.y));

					// define the shape of our dynamic body
					b2PolygonShape crateShape;
					crateShape.SetAsBox((crateWidth * scale) / 2.0f, (crateWidth * scale) / 2.0f);

					// define the physical properties of our shape
					b2FixtureDef crateFd;
					crateFd.shape = &crateShape;
					crateFd.density = 1.0f;
					crateFd.friction = 0.3f;
					crateFd.restitution = 0.2f;

					b2Body *crateBody = world.CreateBody(&crate); // allocate the object to the game world
					crateBody->CreateFixture(&crateFd); // attach the fixture properties to our object

					bool test = false; // example data attachment
					crateBody->SetUserData(&test); // attach some data; does not do anything currently!
				}
			}
		}
		window.clear();
		world.Step(TIMESTEP, VELOCITY, POSITION);

		b2Body *body = world.GetBodyList();
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
						std::cout << *((bool*)body->GetUserData()); // example of getting some data off of the user object

																	//sprite.setRotation(body->GetAngle() / M_PI * 180.0);
						rect.setRotation(convert.radiansToDegrees(body->GetAngle()));

						float x = convert.box2DXToCanvas(position.x);
						float y = convert.box2DYToCanvas(position.y);

						//sprite.setPosition(x, y);
						//window.draw(sprite);
						rect.setPosition(x, y);
						window.draw(rect);

					}
					else // draw shape using a vertexes
					{
						sf::ConvexShape convex;
						convex.setOutlineColor(sf::Color::White);
						convex.setFillColor(sf::Color::Red);
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

		window.display();
	}

	return 0;
}
>>>>>>> e7a97129ea7e7c419357d77cd0ae823cb7c79bfc
