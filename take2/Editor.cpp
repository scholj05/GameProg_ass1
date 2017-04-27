#include "Editor.h"

Editor::Editor(Conversion * convert) {
	m_convert = convert;
}



void Editor::save(b2Body* bodyList) {

	// get a test document
	pugi::xml_document doc;
	doc.load_string("<mainelement><subelement>derp</subelement></mainelement>");
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

	pugi::xml_node subelementnode = doc.child("mainelement").child("subelement");

	std::cout << "Load result: " << doc.child("mainelement").child("subelement").child_value() << std::endl;
	// end::code[]
}