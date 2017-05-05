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
	char bodyname[32] = "body";
	int i = 0;

	b2Body *bodyList = a_bodyList;

	while (bodyList != NULL)
	{
		b2Vec2 position = bodyList->GetPosition();
		b2Fixture *fixture = bodyList->GetFixtureList();

		pugi::xml_node currentnode = doc.child("root").child("bodyList").append_child(bodyname);

		currentnode.append_attribute("posX").set_value(m_convert->box2DXToCanvas(position.x));
		currentnode.append_attribute("posY").set_value(m_convert->box2DXToCanvas(position.y));
		currentnode.append_attribute("angle").set_value(bodyList->GetAngle());

		int tempfixturecount = 0;

		while (fixture != NULL)
		{

			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

			pugi::xml_node fixturenode = currentnode.append_child("fixture");

			char fixturename[32] = "fixture";
			char fintbuffer[16];

			doc.child("root").child("bodyList").child(bodyname).append_child(fixturename);

			for (int j = 0; j < (poly->GetVertexCount()); j++) {
				char vertexname[32] = "vertex";

				pugi::xml_node vertexnode = fixturenode.append_child("vertex");

				vertexnode.append_attribute("posX").set_value(poly->GetVertex(j).x);
				vertexnode.append_attribute("posY").set_value(poly->GetVertex(j).y);

			}

			fixturenode.append_attribute("density").set_value(fixture->GetDensity());
			fixturenode.append_attribute("friction").set_value(fixture->GetFriction());
			fixturenode.append_attribute("restitution").set_value(fixture->GetRestitution());

			fixture = fixture->GetNext();
		}
		bodyList = bodyList->GetNext();
	}

	// save document to file
	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;

}

void Editor::load() {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("save_file.xml");

	pugi::xml_node bodylistnode = doc.child("root").child("bodyList");

	for (pugi::xml_node bodynode = bodylistnode.first_child(); bodynode; bodynode = bodynode.next_sibling())
	{

		std::cout << "posx of this body = " << bodynode.attribute("posX").value() << std::endl;
		std::cout << "posY of this body = " << bodynode.attribute("posY").value() << std::endl;
		std::cout << "angle of this body = " << bodynode.attribute("angle").value() << std::endl;

		for (pugi::xml_node fixturenode = bodynode.first_child(); fixturenode; fixturenode = fixturenode.next_sibling())
		{

			std::cout << "density of this fixture = " << fixturenode.attribute("density").value() << std::endl;
			std::cout << "friction of this fixture = " << fixturenode.attribute("friction").value() << std::endl;
			std::cout << "restitution of this fixture = " << fixturenode.attribute("restitution").value() << std::endl;

				for (pugi::xml_node vertexnode = fixturenode.first_child(); vertexnode; vertexnode = vertexnode.next_sibling())
				{
					std::cout << "posX of this vertex = " << vertexnode.attribute("posX").value() << std::endl;
					std::cout << "posY of this vertex = " << vertexnode.attribute("posY").value() << std::endl;
				}
			
		}
	}

	//std::cout << bodylistnode.name() << std::endl;

	//pugi::xml_node subelementnode = doc.child("mainelement").child("subelement");
	//std::cout << "Load result: " << doc.child("mainelement").child("subelement").child_value() << std::endl;
}

//void Editor::save(b2Body* a_bodyList) {
//
//	// get a test document
//	pugi::xml_document doc;
//	doc.load_string("<mainelement><subelement>derp</subelement></mainelement>");
//
//	// tag::code[]
//	// save document to file
//	std::cout << "Saving result: " << doc.save_file("save_file.xml") << std::endl;
//	// end::code[]
//
//}
//
//void Editor::load() {
//
//	// tag::code[]
//	pugi::xml_document doc;
//
//	pugi::xml_parse_result result = doc.load_file("save_file.xml");
//
//	pugi::xml_node subelementnode = doc.child("mainelement").child("subelement");
//
//	std::cout << "Load result: " << subelementnode.child_value() << std::endl;
//	// end::code[]
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
