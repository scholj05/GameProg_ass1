#pragma once
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Conversion.h"
#include "physics.h"
#include <iostream>
#include <sstream>

class UI
{
private:
	Conversion * m_convert;
	CreateShape * m_shape;
	b2World * m_world;

	sf::Font m_font;
	sf::RectangleShape m_UIBox, m_PowerBarBackground, m_PowerBarLevel, m_designerUIBox;
	sf::Text m_FPSTitle, m_FPSValue, m_BallPositionTitle, m_BallPositionTitleX, 
		m_BallPositionTitleY, m_BallPositionValueX, m_BallPositionValueY, m_StateTitle, m_StateValue,
		m_designerUITitle, m_designerBoxTitle, m_designerBarTitle, m_designerRampTitle;
	sf::Texture m_DirectionArrow;
	sf::Sprite m_ArrowSprite;

	sf::RectangleShape m_designerBox, m_designerBar;
	sf::ConvexShape m_designerRamp;
	bool m_drawDesignerUI = false, m_drawBox = false, m_drawBar = false, m_drawRamp = false,
		m_boxSelected = false, m_barSelected = false, m_rampSelected = false;

public:
	///constructor with references to other classes initialised by main
	UI(sf::RenderWindow &window, Conversion * convert, CreateShape * shape, b2World * world);

	///for updating values based on changing numbers (fps, ball position, ball state, etc)
	void UI::Update(b2Vec2 position, bool isMoving, int FPS);

	///for updating the position and scale of the UI when the screen size changes
	void UpdateScreenPosition(sf::RenderWindow & window);

	///toggle the designer UI being drawn
	void ToggleDrawDesignerUI();

	///updates the scale of the shape
	void UpdateDesignerShapeScale(float scale);

	///sets if a shape is drawn or not individually
	void SetVisibleDesignerShape(int shapeNum, bool visible);

	///set boolean to true if click coords are within shape
	void SelectUIShape(sf::Vector2i);

	///undo shape selections
	void DeselectUIShape();

	///updates the location of the shape
	void UpdateDesignerShape(float posX, float posY);
	
	///for drawing the UI elements (separate of update to allow for less update calls, thus less per game loop)
	void UI::Draw(sf::RenderWindow &window);
	~UI();




};

