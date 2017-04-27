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

		std::string m_posX;
		std::string m_posY;
		std::string m_width;
		std::string m_height;
		std::string m_density;
		std::string m_friction;
		std::string m_restitution;
		std::string m_angle;

};