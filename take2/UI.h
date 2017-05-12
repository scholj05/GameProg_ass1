#pragma once
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Conversion.h"
#include "physics.h"
#include "Level.h"
#include <iostream>
#include <sstream>

class UI
{
private:
	Conversion * m_convert;
	CreateShape * m_shape;
	b2World * m_world;
	sf::RenderWindow * m_window;
	Level * m_level;

	int alpha = 0;
	bool powerBarUp = true;

	sf::Font m_font;
	sf::RectangleShape m_UIBox, m_PowerBarLevel, m_designerUIBox;
	sf::Text m_HelpTitle, m_FPSTitle, m_FPSValue, m_BallPositionTitle, m_BallPositionTitleX, 
		m_BallPositionTitleY, m_BallPositionValueX, m_BallPositionValueY, m_StateTitle, m_StateValue,
		m_arrowDirectionTitle, m_powerBarTitle,
		m_designerUITitle, m_designerBoxTitle, m_designerBarTitle, m_designerRampTitle;
	bool m_arrowLeft = false, m_drawHelp = false;
	sf::Texture m_leftArrowTexture, m_rightArrowTexture, m_instructionsTexture;
	sf::Sprite m_ArrowSprite, m_instructions;

	sf::RectangleShape m_designerBox, m_designerBar;
	sf::ConvexShape m_designerRamp;
	sf::Vector2f m_designerBoxDefaultPosition, m_designerBarDefaultPosition, m_designerRampDefaultPosition;

	bool m_drawDesignerUI = false, m_drawBox = false, m_drawBar = false, m_drawRamp = false;
	CreateShape::ShapeType m_selectedShape;
	int m_shapesThisSession = 0;

	

public:
	///constructor with references to other classes initialised by main
	UI(sf::RenderWindow &window, Conversion * convert, CreateShape * shape, b2World * world, Level * level);

	///for updating values based on changing numbers (fps, ball position, ball state, etc)
	void UI::Update(b2Vec2 position, bool isMoving, int FPS);

	///for updating the position and scale of the UI when the screen size changes
	void UpdateScreenPosition(sf::RenderWindow & window);

	///toggle the designer UI being drawn
	void ToggleDrawDesignerUI();

	///toggle drawing the help overlay
	void ToggleHelp();

	///updates the scale of the shape
	void UpdateDesignerShapeScale(float scale);

	///offset current shape rotation by parameter amount (in degrees)
	void RotateDesignerShape(float rotation);

	///sets if a shape is drawn or not individually
	void SetVisibleDesignerShape(int shapeNum, bool visible);

	///set boolean to true if click coords are within shape
	void SelectUIShape(sf::Vector2i);

	///undo shape selections
	void DeselectUIShape(bool createShape);

	///Set the defined shape back to its original position (position set at creation)
	void ResetShapePos(CreateShape::ShapeType shape);

	///updates the location of the shape
	void UpdateDesignerShape(float posX, float posY);

	void UpdatePowerBar();

	///Resets the alpha level of the power bar to zero and returns the value previous to reset.
	int ResetPowerBar();

	///sets whether the arrow for ball direction faces left or not
	void setBallDirection(bool direction);

	///checks if any shapes were drawn this session to delete, then deletes it
	void DeleteLast();
	
	///for drawing the UI elements (separate of update to allow for less update calls, thus less per game loop)
	void UI::Draw(sf::RenderWindow &window);
	~UI();




};

