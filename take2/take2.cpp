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
#include "Level.h"

//	Main class runs the game loop and handles events/inputs.
//
//	Physics class creates shapes based on a position,
//	bodytype and number of vertices(angularly symmetrical).
//
//	Conversion class converts SFML world coordinates and degrees 
//	to Box2D world coordinates and radians.


bool m_debug = false;
float scale = 0.01;
float scaledWidth;
float scaledHeight;

///list of bodies to be destroyed at next delete phase
std::list<b2Body*> graveyard; 



///code sourced from: https://github.com/SFML/SFML/wiki/Source%3A-Zoom-View-At-%28specified-pixel%29
void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	sf::View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
}

///Handles view movement based on input. Movement amount is scaled to a percentage of the visible world.
void checkView(sf::RenderWindow &window, sf::Vector2i mousePos)
{
	sf::View view(window.getView());
	sf::Vector2f viewSize(view.getSize());
	int scale = 3;
	int movementPadding = 10;

	if (mousePos.x > window.getSize().x + window.getPosition().x - movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		int amount = int(viewSize.x / 100 * scale);
		view.move(amount, 0.0);
	}
	if (mousePos.x <  window.getPosition().x + movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		int amount = int(viewSize.x / 100 * scale);
		view.move(-amount, 0.0);
	}
	if (mousePos.y > window.getSize().y + window.getPosition().y - movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		int amount = int(viewSize.y / 100 * scale);
		view.move(0.0, amount);
	}
	if (mousePos.y < window.getPosition().y + movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		int amount = int(viewSize.y / 100 * scale);
		view.move(0.0, -amount);
	}
	
	window.setView(view);
}

void Cleanup()
{
	for (std::list<b2Body*>::iterator it = graveyard.begin(); it != graveyard.end(); ++it)
	{
		(*it)->GetWorld()->DestroyBody(*it);
	}
	graveyard.clear();
}

int main()
{
	CreateShape m_shape;
	Level level;
	///Box2D value declaration
	b2Vec2 gravity(0.0f, -9.8f);///define gravity
	float TIMESTEP = 1.0f / 60.0f;///step per frame @ 60FPS
	int VELOCITY = 2;///iterations of velocity update per step
	int POSITION = 2;///iterations of position update per step
	b2World * world = new b2World(gravity);///define world
	world->SetAllowSleeping(false);///don't allow objects in box2D world to paus
								   
	///SFML window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Take 2: more successful than take 1");
	sf::Vector2f screenSize(sf::Vector2i(window.getSize().x, window.getSize().y));
	sf::View view(sf::Vector2f(float(window.getSize().x / 2), float(window.getSize().y / 2)), screenSize);
	sf::View UI(window.getDefaultView());
	window.setView(view);
	window.setFramerateLimit(60); // control how fast the screen is refreshed (fps)
	float zoomAmount = 1.1f; //used for zoom adjustment. 1.1 = 10%

	sf::Font font;
	if (!font.loadFromFile("../resources/arial.ttf"))
	{
		std::cout << "Could not load arial.ttf font" << std::endl;
	}
	sf::Clock clock;
	float lastTime = 0;
	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(20);
	fpsText.setPosition(12, 0);

	///setup conversion class
	scaledWidth = scale * (window.getSize().x);
	scaledHeight = scale * (window.getSize().y);
	Conversion convert(scale, scaledWidth, scaledHeight);

	///Define shapes and add to b2World
	level.Level1(world, &convert, &m_shape);
	
	
	///Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
				b2Vec2 mouse = b2Vec2(convert.canvasXToBox2D(worldPos.x), convert.canvasYToBox2D(worldPos.y));
				b2PolygonShape particle;
				particle = m_shape.calculateRandomShape(mouse);
				
				b2FixtureDef particleFixture = m_shape.setFixture(1, 0.3, 0.5);
				particleFixture.shape = &particle;

				b2BodyDef particleBodyDef;
				particleBodyDef.type = b2BodyType::b2_dynamicBody;

				b2Body * particleBody = world->CreateBody(&particleBodyDef);
				particleBody->CreateFixture(&particleFixture);

				sf::Color colour = sf::Color::Red;//sf::Color(convert.getRandomInt(0, 255), convert.getRandomInt(0, 255), convert.getRandomInt(0, 255));
				particleBody->SetUserData(&colour);
			}

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
				b2Vec2 mouse = b2Vec2(convert.canvasXToBox2D(worldPos.x), convert.canvasYToBox2D(worldPos.y));
				b2PolygonShape particle;
				particle = m_shape.calculateRandomShape(mouse);

				b2FixtureDef particleFixture = m_shape.setFixture(1, 0.3, 0.5);
				particleFixture.shape = &particle;

				b2BodyDef particleBodyDef;
				particleBodyDef.type = b2BodyType::b2_staticBody;

				b2Body * particleBody = world->CreateBody(&particleBodyDef);
				particleBody->CreateFixture(&particleFixture);

				sf::Color colour = sf::Color::Red;//sf::Color(convert.getRandomInt(0, 255), convert.getRandomInt(0, 255), convert.getRandomInt(0, 255));
				particleBody->SetUserData(&colour);
				
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
				else if (event.mouseWheelScroll.delta < 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
			}
		}
		window.clear();

		checkView(window, sf::Mouse::getPosition());

		if (m_debug)
		{
		}

		level.updateKinematicObjects();

		world->Step(TIMESTEP, VELOCITY, POSITION);

		///clear bodies scheduled for deletion
		//std::cout << "graveyard count: " << graveyard.size() << std::endl;
		Cleanup();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_shape.testMethod(world);


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
						//if (!(level.getworldBoundary().contains(sf::Vector2f(convert.box2DXToCanvas(body->GetPosition().x), convert.box2DYToCanvas(body->GetPosition().y)))))
						int buffer = 1000;
						sf::Vector2f bodyPos(convert.box2DXToCanvas(body->GetPosition().x), convert.box2DYToCanvas(body->GetPosition().y));
						sf::FloatRect levelBoundary = level.getworldBoundary();
						if (bodyPos.x > levelBoundary.left + levelBoundary.width + buffer ||
							bodyPos.x < levelBoundary.left - buffer ||
							bodyPos.y > levelBoundary.top + levelBoundary.height + buffer ||
							bodyPos.y < levelBoundary.top - buffer)
						{
							std::cout << "pos for death: " << bodyPos.x << ", " << bodyPos.y << std::endl;
							graveyard.push_back(body);
							
							//get the visible area of world from the view as a float rect
							//sf::FloatRect visibleScreen(window.mapPixelToCoords(sf::Vector2i(0, 0)), window.getView().getSize());
							//if the visible screen rect does not contain the body, add it to the graveyard
							//if (!visibleScreen.contains(sf::Vector2f(convert.box2DYToCanvas(body->GetPosition().x), convert.box2DYToCanvas(body->GetPosition().y))))
							//{
							//	graveyard.push_back(body);
							//}
						}

						else
						{
							sf::ConvexShape dynamic;
							//dynamic.setOutlineColor(sf::Color::White);
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
		
		sf::Vector2f textPos = sf::Vector2f(10, 10);//window.mapPixelToCoords(sf::Vector2i(10, 10));
		fpsText.setPosition(textPos);
		sf::View currentView = window.getView();
		window.setView(window.getDefaultView());
		window.draw(fpsText);
		window.setView(currentView);
		window.display();
	}

	return 0;
}