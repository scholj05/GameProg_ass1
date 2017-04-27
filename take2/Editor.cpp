#include "Editor.h"

Editor::Editor(Conversion * convert) {
	m_convert = convert;
}



void Editor::save(b2Body* bodyList) {

	// get a test document
	pugi::xml_document doc;
	doc.load_string("<root><subelement>derp</subelement></root>");
	while (bodyList != NULL)
	{

	}
	// tag::code[]
	// save document to file
	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;
	// end::code[]

}

void Editor::load() {

	// tag::code[]
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("save_file.xml");

	pugi::xml_node subelementnode = doc.child("root").child("subelement");

	std::cout << "Load result: " << doc.child("root").child("subelement").child_value() << std::endl;
	// end::code[]
}

Parameters::Parameters() {
	std::string m_b2BodyDef = "";
	std::string m_b2BodyDefType = "";
	std::string m_calculateRectangle = "";
	std::string m_recPosition = "";
	std::string m_recWidth = "";
	std::string m_recHeight = "";
	std::string m_rotation = "";
	std::string m_b2FixtureDef = "";
	std::string m_density = "";
	std::string m_friction = "";
	std::string m_restitution = "";
}

Parameters::Parameters(std::string b2bodydef, std::string b2bodydeftype, std::string calcrec, std::string recpos,
	std::string recwid, std::string rechei, std::string rot, std::string fixdef, std::string density, std::string friction, std::string restitution) {
	std::string m_b2BodyDef = b2bodydef;
	std::string m_b2BodyDefType = b2bodydeftype;
	std::string m_calculateRectangle = calcrec;
	std::string m_recPosition = recpos;
	std::string m_recWidth = recwid;
	std::string m_recHeight = rechei;
	std::string m_rotation = rot;
	std::string m_b2FixtureDef = fixdef;
	std::string m_density = density;
	std::string m_friction = friction;
	std::string m_restitution = restitution;
}

std::string Parameters::getb2BodyDef() {
	return m_b2BodyDef;
}

void Parameters::setb2BodyDef(std::string b2BodyDef) {
	m_b2BodyDef = b2BodyDef;
}

