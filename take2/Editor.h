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
		std::string m_b2BodyDef;
		std::string m_b2BodyDefType;
		std::string m_calculateRectangle;
		std::string m_recPosition;
		std::string m_recWidth;
		std::string m_recHeight;
		std::string m_rotation;
		std::string m_b2FixtureDef;
		std::string m_density;
		std::string m_friction;
		std::string m_restitution;


	public:

		Parameters::Parameters();
		Parameters::Parameters(std::string b2bodydef, std::string b2bodydeftype, std::string calcrec, std::string recpos,
			std::string recwid, std::string rechei, std::string rot, std::string fixdef, std::string density, std::string friction, std::string restitution);
		std::string getb2BodyDef();
		void setb2BodyDef(std::string b2BodyDef);
};