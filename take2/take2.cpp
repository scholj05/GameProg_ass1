#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <random>


#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Conversion.h"
#include "physics.h"
#include "Level.h"
#include "MyShape.h"
#include "UI.h"
#include "Editor.h"
#include "hole.h"

//	Main class runs the game loop and handles events/inputs.
//
//	Physics class creates shapes based on a position,
//	bodytype and number of vertices(angularly symmetrical).
//
//	Conversion class converts SFML world coordinates and degrees 
//	to Box2D world coordinates and radians.


enum GameState {
	design = 0,
	play = 1,
	loadsave = 2
};

bool m_debug = false;
float scale = 0.01f;
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
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		int amount = int(viewSize.x / 100 * scale);
		view.move(amount, 0.0f);
	}
	if (mousePos.x <  window.getPosition().x + movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		int amount = int(viewSize.x / 100 * scale);
		view.move(-amount, 0.0f);
	}
	if (mousePos.y > window.getSize().y + window.getPosition().y - movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		int amount = int(viewSize.y / 100 * scale);
		view.move(0.0f, amount);
	}
	if (mousePos.y < window.getPosition().y + movementPadding
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		int amount = int(viewSize.y / 100 * scale);
		view.move(0.0f, -amount);
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
	GameState game_state = GameState::play;
	bool hitLeft = false;
	///timers and timer-related variables
	sf::Clock fpsClock, updateUIClock;
	float lastTime = 0;

	///variables of other classes
	CreateShape m_shape;
	Level level;
	
	///list for ball class objects
	std::list<MyShape*>shapeList;

	///Box2D value declaration
	b2Vec2 gravity(0.0f, -9.8f);///define gravity
	float TIMESTEP = 1.0f / 60.0f;///step per frame @ 60FPS
	int VELOCITY = 2;///iterations of velocity update per step
	int POSITION = 2;///iterations of position update per step
	b2World * world = new b2World(gravity);///define world
	world->SetAllowSleeping(true);///don't allow objects in box2D world to paus
								   
	///SFML window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Take 2: more successful than take 1", sf::Style::Fullscreen);

	///SFML Views
	sf::Vector2f screenSize(sf::Vector2i(window.getSize().x, window.getSize().y));
	sf::View worldView(sf::Vector2f(1000.f, 1000.f), screenSize);
	sf::View UIView(window.getDefaultView());
	window.setView(worldView);      ///apply the view to the window
	window.setFramerateLimit(60);   /// control how fast the screen is refreshed (fps)
	float zoomAmount = 1.1f;        ///used for zoom adjustment. 1.1 = 10%


	///setup conversion class
	scaledWidth = scale * (window.getSize().x);
	scaledHeight = scale * (window.getSize().y);
	Conversion convert(scale, scaledWidth, scaledHeight);

	///initialise classes that require info from window and other classes first
	UI gameUI(window, &convert, &m_shape, world);
	Editor editor(&convert);
	
	///Define shapes and add to b2World
	level.Level1(world, &convert, &m_shape, 2000.f, 2000.f);
	MyShape * myBall = new MyShape(200.f, 200.f, b2BodyType::b2_dynamicBody, 20, sf::Color::Red, world, convert);
	bool isBallMoving;

	///Create instance of hole class


	///Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if (game_state == GameState::design)
				{
					
				}
				else if (game_state == GameState::play)
				{
					window.close();
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (game_state == GameState::design)
				{
					gameUI.SelectUIShape(sf::Mouse::getPosition(window));
				}
				else if (game_state == GameState::play)
				{
					if (hitLeft)
						myBall->Putt(-1);
					else
						myBall->Putt(2);
				}
			}

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				if (game_state == GameState::design)
				{
					gameUI.DeselectUIShape(true);
				}
				else if (game_state == GameState::play)
				{
					myBall->Jump(1);
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F8)
				{
					if (game_state == GameState::design)
					{
						game_state = GameState::play;
						gameUI.ToggleDrawDesignerUI();
					}
					else if (game_state == GameState::play)
					{
						game_state = GameState::design;
						gameUI.ToggleDrawDesignerUI();
					}
						
				}
				if (event.key.code == sf::Keyboard::F11)
				{
					//run save here
					editor.save(world->GetBodyList());
				}
				if (event.key.code == sf::Keyboard::F12)
				{
					//run load here
					editor.load();
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space && !(myBall->isMoving()))
				{
					float powerLevel = gameUI.ResetPowerBar();
					if (powerLevel > 0)
					{
						if (hitLeft)
							myBall->Putt(((powerLevel / 50) + 1) * -1);
						else
							myBall->Putt(powerLevel / 50 + 1);
					}
					

				}
				if (event.key.code == sf::Keyboard::D)
				{
					hitLeft = !hitLeft;
					gameUI.setBallDirection(hitLeft);
				}
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
				{
					if (event.mouseWheelScroll.delta > 0)
						gameUI.UpdateDesignerShapeScale(0.5);
					else if (event.mouseWheelScroll.delta < 0)
						gameUI.UpdateDesignerShapeScale(-0.5);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
				{
					if (event.mouseWheelScroll.delta > 0)
						gameUI.RotateDesignerShape(22.5f);
					else if (event.mouseWheelScroll.delta < 0)
						gameUI.RotateDesignerShape(-22.5f);
				}
				else
				{
					if (event.mouseWheelScroll.delta > 0)
						zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
					else if (event.mouseWheelScroll.delta < 0)
						zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
				}
			}
		}
		
		window.clear();

		///update view
		checkView(window, sf::Mouse::getPosition());

		level.UpdateKinematicObjects();

		///call isMoving before the worldStep to check the ball location 
		///before it gets updated and previous location reset
		isBallMoving = myBall->isMoving();

		///update the box2d world
		world->Step(TIMESTEP, VELOCITY, POSITION);

		///clear bodies scheduled for deletion
		Cleanup();


		b2Body *body = world->GetBodyList();
		int bodyCount = 0;
		while (body != NULL)
		{
			bodyCount++;
			b2Vec2 position = body->GetPosition();
			b2Fixture *fixture = body->GetFixtureList();

			while (fixture != NULL)
			{
				switch (fixture->GetType())
				{
				case b2Shape::e_polygon:
				{
					b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

					if (body->GetType() == b2BodyType::b2_staticBody || body->GetType() == b2BodyType::b2_kinematicBody)
					{
						sf::ConvexShape convex;
						convex.setFillColor(sf::Color::Green);
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
		//std::cout << "body count: " << bodyCount << std::endl;
		bodyCount = 0;
		/*
		for (std::list<MyShape*>::iterator it = shapeList.begin(); it != shapeList.end(); ++it)
		{
			(*it)->Update();
			(*it)->Draw(window);
		}*/

		//power level stuff
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (!myBall->isMoving())//only hit ball when ball isn't moving
				gameUI.UpdatePowerBar();
		}

		myBall->Update();
		myBall->Draw(window);

		gameUI.UpdateDesignerShape(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		float currentTime = fpsClock.restart().asSeconds();
		int fps = 1.f / currentTime;

		///only update the UI 8 times a second instead of 60
		if (updateUIClock.getElapsedTime().asMilliseconds() > 125)
		{
			updateUIClock.restart();
			gameUI.Update(myBall->GetBodyPosition(), myBall->isMoving(), fps);
		}

		///update world view to current view, then switch to UI view
		worldView = window.getView();
		window.setView(UIView);

		///draw UI elements
		//window.draw(fpsText);
		
		gameUI.Draw(window);
		///switch back to the world view and display the draws
		window.setView(worldView);
		window.display();
	}

	return 0;
}