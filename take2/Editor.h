#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Level.h"
#include "MyShape.h"
#include "physics.h"
#include "..\resources\pugixml-1.8\src\pugixml.hpp"

class Editor{
	private:



	public:
		void Editor::editor();
		pugi::xml_document m_doc;
		void save();

	};

