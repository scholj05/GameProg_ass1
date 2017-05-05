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
	char bodyname[32] = "body ";
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

		parameters.m_posX = char(m_convert->box2DXToCanvas(position.x));
		char tempposX = parameters.m_posX;
		doc.child("root").child("bodyList").append_child(bodyname).append_child("posX").text().set(tempposX);

		parameters.m_posY = char(m_convert->box2DXToCanvas(position.y));
		char tempposY = parameters.m_posY;
		doc.child("root").child("bodyList").child(bodyname).append_child("posY").text().set(tempposY);

		parameters.m_angle = char(bodyList->GetAngle());
		char tempangle = parameters.m_angle;
		doc.child("root").child("bodyList").child(bodyname).append_child("angle").text().set(tempangle);

		while (fixture != NULL)
		{


			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
			parameters.m_vertexcount = char(poly->GetVertexCount());
			char tempvertexcount = parameters.m_vertexcount;
			doc.child("root").child("bodyList").child(bodyname).append_child("vertexcount").text().set(tempvertexcount);

			for (int j = 0; j < (poly->GetVertexCount()); j++) {
				char vertexname[32] = "vertex ";
				char aintbuffer[16];
				sprintf(aintbuffer, "%d", j);
				strcat(vertexname, aintbuffer);

				char vposX = char(poly->GetVertex(j).x);
				char vposY = char(poly->GetVertex(j).y);

				doc.child("root").child("bodyList").child(bodyname).append_child(vertexname).append_child("x").text().set(vposX);
				doc.child("root").child("bodyList").child(bodyname).child(vertexname).append_child("y").text().set(vposY);

				delete[] vertexname;

			}

			parameters.m_density = char(fixture->GetDensity());
			char tempdensity = parameters.m_density;
			doc.child("root").child("bodyList").child(bodyname).append_child("density").text().set(tempdensity);

			parameters.m_friction = char(fixture->GetFriction());
			char tempfriction = parameters.m_friction;
			doc.child("root").child("bodyList").child(bodyname).append_child("friction").text().set(tempfriction);

			parameters.m_restitution = char(fixture->GetRestitution());
			char temprestitution = parameters.m_restitution;
			doc.child("root").child("bodyList").child(bodyname).append_child("restitution").text().set(temprestitution);


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

	pugi::xml_node bodylistnode = doc.child("root").child("bodyList");

	for (pugi::xml_node body = bodylistnode.first_child(); body != NULL; body = body.next_sibling())
	{
		std::cout << "body:" << body.name() << std::endl;

		std::cout << std::endl;
	}
	//std::cout << "Load result: " << doc.child("root").child("bodyList").child_value() << std::endl;
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
