#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>

#include "physics.h"
#include "Conversion.h"

class Level
{
private:
	CreateShape * m_shape;
	Conversion * m_convert;
	b2World * m_world;

	int m_scale = 0;
	sf::FloatRect level1WorldBoundary;

	b2PolygonShape topWall, bottomWall, leftWall, rightWall,
					leftPusher, rightPusher,
					windmillH, windmillV;
	b2Body *wallBody, *leftPusherBody, *rightPusherBody, *windmillBody;

	bool leftPusherMoveLeft, rightPusherMoveRight;

	

public:
	std::list<b2Body*>staticList, kinematicList;

	void Level::Level1(b2World * world, Conversion * convert, CreateShape * shape, float boundaryX, float boundaryY);
	void Level::CreateWalls(b2World * world, float boundaryX, float boundaryY);
	void Level::UpdateKinematicObjects();
	b2Body * Level::GetWall();

	///return the static body list
	std::list<b2Body*> Level::GetStaticList();

	///add a body to the static body list
	void PushStaticList(b2Body * body);

	///return the kinematic body list
	std::list<b2Body*> Level::GetKinematicList();

	///add a body to the kinematic body list
	void PushKinematicList(b2Body * body);

	sf::FloatRect Level::getworldBoundary() { return level1WorldBoundary; };

};

