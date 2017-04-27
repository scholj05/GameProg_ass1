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
	sf::RectangleShape m_UIBox, m_PowerBarBackground, m_PowerBarLevel, m_designerUIBox;
	sf::Text m_FPSTitle, m_FPSValue, m_BallPositionTitle, m_BallPositionTitleX, 
		m_BallPositionTitleY, m_BallPositionValueX, m_BallPositionValueY, m_StateTitle, m_StateValue,
		m_designerUITitle, m_designerBoxTitle, m_designerBarTitle, m_designerRampTitle;
	sf::Texture m_DirectionArrow;
	sf::Sprite m_ArrowSprite;

	sf::RectangleShape m_designerBox, m_designerBar;
	sf::ConvexShape m_designerRamp;
	bool m_drawDesignerUI = false, m_drawBox = false, m_drawBar = false, m_drawRamp = false;

public:
	UI(sf::RenderWindow &window, Conversion * convert);

	///for updating values based on changing numbers (fps, ball position, ball state, etc)
	void UI::Update(b2Vec2 position, bool isMoving, int FPS);

	///for updating the position and scale of the UI when the screen size changes
	void UpdateScreenPosition(sf::RenderWindow & window);

	void DrawDesignerUI();
	///sets if the shape is drawn or not
	void SetVisibleDesignerShape(int shapeNum, bool visible);

	///updates the scale and location of the shape
	void UpdateDesignerShape(int shapeNum, float posX, float posY, float scale);
	
	///for drawing the UI elements (separate of update to allow for less update calls, thus less per game loop)
	void UI::Draw(sf::RenderWindow &window);
	~UI();




};

