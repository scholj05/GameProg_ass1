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

