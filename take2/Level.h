/*
*	This file and its contents were written by the author, unless stated otherwise.
*	The code is in no way guaranteed to be in working condition,
*	nor does the author claim any responsibility for negative outcomes of running
*	the contents of this file.
*  Any use of this file must be done with the permission of the author.
*
*	@author		Jesse Schollitt
*/

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
	///public lists for use from whole game
	std::list<b2Body*>staticList, kinematicList, graveyard, tempDelete;

	///constructor
	void Level::Level1(b2World * world, Conversion * convert, CreateShape * shape, float boundaryX, float boundaryY);

	///method for creating the boundaries of the world
	void Level::CreateWalls(b2World * world, float boundaryX, float boundaryY);

	///moves kinematic objects within defined movement
	void Level::UpdateKinematicObjects();

	///return the boundary
	b2Body * Level::GetWall();

	///return the static body list
	std::list<b2Body*> Level::GetStaticList();

	///add a body to the static body list
	void PushStaticList(b2Body * body);

	///return the kinematic body list
	std::list<b2Body*> Level::GetKinematicList();

	///add a body to the kinematic body list
	void PushKinematicList(b2Body * body);

	///remove objects from the world at the correct time
	void Level::Cleanup();

	///Add body to the graveyard
	void Level::Destroy(b2Body* body);

	///Clears all user-made objects from the world
	void ClearWorld();

	///returns world boundary float rect for contains check
	sf::FloatRect Level::getworldBoundary() { return level1WorldBoundary; };

};

