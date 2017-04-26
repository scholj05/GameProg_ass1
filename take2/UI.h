#pragma once
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Conversion.h"
#include <iostream>
#include <sstream>

class UI
{
private:
	Conversion * m_convert;
	sf::Font m_font;
	sf::RectangleShape m_UIBox, m_PowerBarBackground, m_PowerBarLevel;
	sf::Text m_FPSTitle, m_FPSValue, m_BallPositionTitle, m_BallPositionTitleX, 
		m_BallPositionTitleY, m_BallPositionValueX, m_BallPositionValueY, m_StateTitle, m_StateValue;
	sf::Texture m_DirectionArrow;
	sf::Sprite m_ArrowSprite;

	//positions of ball for use in the m_StateValue (whether ball is moving). 
	//Could also be done from method call in ball class (probably better that way, oh well).
	b2Vec2 m_lastPosition;
	b2Vec2 m_currentPosition;

public:
	UI(sf::RenderWindow &window, Conversion * convert);
	//for updating values based on changing numbers (fps, ball position, ball state, etc)
	void UI::Update(b2Vec2 position, bool isMoving, int FPS);
	//for updating the position and scale of the UI when the screen size changes
	void UpdateScreenPosition(sf::RenderWindow & window);
	//for drawing the UI elements (separate of update to allow for less update calls, thus less per game loop)
	void UI::Draw(sf::RenderWindow &window);
	//void CreateUIBox(sf::RenderWindow &window);
	//void CreateUIText(std::string text, sf::Font font, float posX, float posY, int fontSize);
	~UI();




};

