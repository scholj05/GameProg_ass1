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

	int m_scale = 0;
	sf::FloatRect level1WorldBoundary;

	b2PolygonShape topWall, bottomWall, leftWall, rightWall,
					leftPusher, rightPusher,
					windmillH, windmillV;
	b2Body *wallBody, *leftPusherBody, *rightPusherBody, *windmillBody;

	bool leftPusherMoveLeft, rightPusherMoveRight;

public:
	void Level::Level1(b2World * world, Conversion * convert, CreateShape * shape, float boundaryX, float boundaryY);
	void updateKinematicObjects();
	sf::FloatRect Level::getworldBoundary() { return level1WorldBoundary; };

};

