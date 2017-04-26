#include "Editor.h"

void Editor::editor() {

}



void Editor::save() {

	// get a test document
	pugi::xml_document doc;
	doc.load_string("<foo bar='baz'>hey</foo>");

	// tag::code[]
	// save document to file
	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;
	// end::code[]

}

void Editor::load() {

	// tag::code[]
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("save_file.xml");

	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
	// end::code[]
}