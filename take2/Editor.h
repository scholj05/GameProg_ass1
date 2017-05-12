#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Box2D\Box2D.h"
#include "Level.h"
#include "MyShape.h"
#include "physics.h"
#include "Conversion.h"
#include "..\resources\pugixml-1.8\src\pugixml.hpp"

class Editor{
	private:
		Conversion * m_convert;
		CreateShape * m_shape;
		b2World * m_world;
		sf::RenderWindow * m_window;
		Level * m_level;

	public:
		Editor(sf::RenderWindow &window, Conversion * convert, CreateShape * shape, b2World * world, Level * level);
		pugi::xml_document m_doc;
		void save(std::list<b2Body*> bodyList);
		void load();

};