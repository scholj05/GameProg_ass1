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

	public:
		Editor(Conversion * convert);
		pugi::xml_document m_doc;
		void save(b2Body* bodyList);
		void load();

};

class Parameters {
	private:



	public:

		Parameters::Parameters();
		Parameters::Parameters(std::string posX, std::string posY, std::string width, std::string height,
			std::string density, std::string friction, std::string restitution, std::string angle);

		char m_posX;
		char m_posY;
		char m_vertexcount;
		//char m_fixturecount;
		char m_vertexvalue;
		char m_density;
		char m_friction;
		char m_restitution;
		char m_angle;

};