#include "Editor.h"
#include "Conversion.h"
#include <iostream>
#include <sstream>

Editor::Editor(Conversion * convert) {
	m_convert = convert;
}

void Editor::save(b2Body* bodyList) {

	b2Body *body = bodyList;
	while (bodyList != NULL)
	{
		b2Vec2 position = body->GetPosition();
		b2Fixture *fixture = body->GetFixtureList();
		Parameters parameters = Parameters();

		while (fixture != NULL)
		{
			std::ostringstream posXBuffer;
			posXBuffer << int(m_convert->box2DXToCanvas(position.x));
			parameters.m_posX = (posXBuffer.str());

			std::ostringstream posYBuffer;
			posYBuffer << int(m_convert->box2DYToCanvas(position.y));
			parameters.m_posY = (posYBuffer.str());

			fixture = fixture->GetNext();
		}
		body = body->GetNext();
	}

	// get a test document
	pugi::xml_document doc;
	doc.load_string("<root><subelement>derp</subelement></root>");
	
	// save document to file
	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;

}

void Editor::load() {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("save_file.xml");

	pugi::xml_node subelementnode = doc.child("root").child("subelement");

	std::cout << "Load result: " << doc.child("root").child("subelement").child_value() << std::endl;
}

Parameters::Parameters() {
	std::string m_posX = "";
	std::string m_posY = "";
	std::string m_width = "";
	std::string m_height = "";
	std::string m_density = "";
	std::string m_friction = "";
	std::string m_restitution = "";
	std::string m_angle = "";
}

Parameters::Parameters(std::string posX, std::string posY, std::string width, std::string height,
	std::string density, std::string friction, std::string restitution, std::string angle) {
	std::string m_posX = posX;
	std::string m_posY = posY;
	std::string m_width = width;
	std::string m_height = height;
	std::string m_density = density;
	std::string m_friction = friction;
	std::string m_restitution = restitution;
	std::string m_angle = angle;
}
