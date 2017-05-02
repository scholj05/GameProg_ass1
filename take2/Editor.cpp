#include "Editor.h"
#include "Conversion.h"
#include <iostream>
#include <sstream>

Editor::Editor(Conversion * convert) {
	m_convert = convert;
}

void Editor::save(b2Body* a_bodyList) {

	// get a base document
	pugi::xml_document doc;
	doc.load_string("<root><bodyList></bodyList></root>");
	char bodyname[32] = "Body ";
	char intbuffer[16];
	int i = 0;
	b2Body *bodyList = a_bodyList;
	while (bodyList != NULL)
	{
		b2Vec2 position = bodyList->GetPosition();
		b2Fixture *fixture = bodyList->GetFixtureList();
		Parameters parameters = Parameters();

		sprintf(intbuffer, "%d", i);
		strcat(bodyname, intbuffer);

		while (fixture != NULL)
		{

			//std::ostringstream posXBuffer;
			//posXBuffer << int(m_convert->box2DXToCanvas(position.x));
			parameters.m_posX = char(m_convert->box2DXToCanvas(position.x));
			char tempposX = parameters.m_posX;
			std::cout << tempposX << std::endl;
			doc.child("root").child("bodyList").append_child(bodyname).append_child("posX").text().set(tempposX);

			//std::ostringstream posYBuffer;
			//posYBuffer << int(m_convert->box2DYToCanvas(position.y));
			parameters.m_posY = char(m_convert->box2DXToCanvas(position.y));
			char tempposY = parameters.m_posY;
			std::cout << tempposY << std::endl;
			doc.child("root").child("bodyList").child(bodyname).append_child("posY").text().set(tempposY);

			
			fixture = fixture->GetNext();
		}
		i += 1;
		bodyname[5] = NULL;
		bodyList = bodyList->GetNext();
	}

	// save document to file
	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;

}

void Editor::load() {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("save_file.xml");

	pugi::xml_node subelementnode = doc.child("root").child("bodyList");

	std::cout << "Load result: " << doc.child("root").child("bodyList").child_value() << std::endl;
}

//struct xml_string_writer : pugi::xml_writer
//{
//	std::string result;
//
//	virtual void write(const void* data, size_t size)
//	{
//		result.append(static_cast<const char*>(data), size);
//	}
//};
//
//std::string node_to_string(pugi::xml_node node)
//{
//	xml_string_writer writer;
//	node.print(writer);
//
//	return writer.result;
//}

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
