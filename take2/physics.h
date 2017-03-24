
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Shape
{
private:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_bodyShape;
	b2FixtureDef m_bodyFix;
	sf::RectangleShape m_shape; //SFML shape
public:
	Shape(b2World & world);
	void ShapeSetWorld(b2World & world);
	b2Body* GetBody(); // Get Box2d body
	sf::Shape & GetShape();
	void update(); // Get SFML shape
	void ResetPosition(b2World & world); 
	void jump(float angle);
	~Shape();

	
	Shape(b2World & world, b2BodyType bodyType, b2Vec2 position, float radius, int verticeCount);

	b2PolygonShape createShape(float radius, float verticeCount);

};
