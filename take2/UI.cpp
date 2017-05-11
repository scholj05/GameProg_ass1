#include "UI.h"



UI::UI(sf::RenderWindow &window, Conversion * convert, CreateShape * shape, b2World * world, Level * level)
{
	m_convert = convert;
	m_shape = shape;
	m_world = world;
	m_window = &window;
	m_level = level;
	if (!m_font.loadFromFile("../resources/arial.ttf"))
	{
		std::cout << "Could not load arial.ttf font" << std::endl;
	}

	if (!m_leftArrowTexture.loadFromFile("../resources/left_arrow.png"))
	{
		std::cout << "Could not load left_arrow.png" << std::endl;
	}

	if (!m_rightArrowTexture.loadFromFile("../resources/right_arrow.png"))
	{
		std::cout << "Could not load right_arrow.png" << std::endl;
	}
	m_ArrowSprite.setTexture(m_rightArrowTexture);

	int charHeight, padding;
	m_UIBox.setSize(sf::Vector2f(float(window.getSize().x / 10), float(window.getSize().y)));
	m_UIBox.setOrigin(m_UIBox.getSize().x / 2, m_UIBox.getSize().y / 2);
	m_UIBox.setPosition(m_UIBox.getOrigin());
	m_UIBox.setFillColor(sf::Color(150, 150, 150, 100));
	m_UIBox.setOutlineColor(sf::Color::Black);
	m_UIBox.setOutlineThickness(5.f);
	
	charHeight = int(m_UIBox.getSize().x / 8);
	padding = charHeight / 2;

	int leftAlign = int(m_UIBox.getPosition().x - m_UIBox.getSize().x / 2 + padding);
	int rightAlign = int(m_UIBox.getPosition().x + charHeight + padding);

	m_FPSTitle.setCharacterSize(charHeight);
	m_FPSTitle.setPosition(float(leftAlign), 
		m_UIBox.getPosition().y - m_UIBox.getSize().y / 2 + float(padding));
	m_FPSTitle.setString(sf::String("FPS:"));
	m_FPSTitle.setFont(m_font);

	m_FPSValue.setCharacterSize(charHeight);
	m_FPSValue.setPosition(float(rightAlign),
		m_FPSTitle.getPosition().y);
	m_FPSValue.setString(sf::String("00"));
	m_FPSValue.setFont(m_font);

	m_BallPositionTitle.setCharacterSize(charHeight);
	m_BallPositionTitle.setPosition(leftAlign,
		m_FPSTitle.getPosition().y + padding + charHeight + charHeight);
	m_BallPositionTitle.setString(sf::String("Ball Position"));
	m_BallPositionTitle.setFont(m_font);

	m_BallPositionTitleX.setCharacterSize(charHeight);
	m_BallPositionTitleX.setPosition(leftAlign,
		m_BallPositionTitle.getPosition().y + padding + charHeight);
	m_BallPositionTitleX.setString(sf::String("X:"));
	m_BallPositionTitleX.setFont(m_font);

	m_BallPositionValueX.setCharacterSize(charHeight);
	m_BallPositionValueX.setPosition(rightAlign,
		m_BallPositionTitleX.getPosition().y);
	m_BallPositionValueX.setString(sf::String("00"));
	m_BallPositionValueX.setFont(m_font);

	m_BallPositionTitleY.setCharacterSize(charHeight);
	m_BallPositionTitleY.setPosition(leftAlign,
		m_BallPositionValueX.getPosition().y + padding + charHeight);
	m_BallPositionTitleY.setString(sf::String("Y:"));
	m_BallPositionTitleY.setFont(m_font);

	m_BallPositionValueY.setCharacterSize(charHeight);
	m_BallPositionValueY.setPosition(rightAlign,
		m_BallPositionTitleY.getPosition().y);
	m_BallPositionValueY.setString(sf::String("00"));
	m_BallPositionValueY.setFont(m_font);

	m_StateTitle.setCharacterSize(charHeight);
	m_StateTitle.setPosition(leftAlign,
		m_BallPositionTitleY.getPosition().y + padding + charHeight + charHeight);
	m_StateTitle.setString(sf::String("State:"));
	m_StateTitle.setFont(m_font);

	m_StateValue.setCharacterSize(charHeight);
	m_StateValue.setPosition(rightAlign - charHeight - charHeight,
		m_StateTitle.getPosition().y);
	m_StateValue.setString(sf::String(""));
	m_StateValue.setFont(m_font);

	m_arrowDirectionTitle.setFont(m_font);
	m_arrowDirectionTitle.setCharacterSize(charHeight);
	m_arrowDirectionTitle.setOrigin(charHeight * 2, charHeight / 2);
	m_arrowDirectionTitle.setPosition(m_UIBox.getPosition().x, m_StateValue.getPosition().y + padding + (charHeight * 5));
	m_arrowDirectionTitle.setString("Direction");

	m_ArrowSprite.setScale(0.1f, 0.1f);
	m_ArrowSprite.setOrigin(25, 25);
	m_ArrowSprite.setPosition(m_arrowDirectionTitle.getPosition().x - 50, m_arrowDirectionTitle.getPosition().y + 50);
	

	m_PowerBarLevel.setSize(sf::Vector2f(m_UIBox.getSize().x / 2, m_UIBox.getSize().y / 3));
	m_PowerBarLevel.setOrigin(m_PowerBarLevel.getSize().x / 2, m_PowerBarLevel.getSize().y / 2);
	m_PowerBarLevel.setPosition(m_UIBox.getPosition().x, m_UIBox.getPosition().y + m_UIBox.getSize().y / 4 - padding);
	m_PowerBarLevel.setFillColor(sf::Color(255, 0, 0, 0));
	m_PowerBarLevel.setOutlineThickness(3);
	m_PowerBarLevel.setOutlineColor(sf::Color::Black);

	m_powerBarTitle.setFont(m_font);
	m_powerBarTitle.setCharacterSize(charHeight);
	m_powerBarTitle.setOrigin(charHeight * 3, charHeight / 2);
	m_powerBarTitle.setPosition(m_PowerBarLevel.getPosition().x, m_PowerBarLevel.getPosition().y - m_PowerBarLevel.getSize().y / 2 - charHeight - padding);
	m_powerBarTitle.setString("Power Meter");


	m_designerUIBox.setSize(sf::Vector2f(float(window.getSize().x / 10), float(window.getSize().y)));
	m_designerUIBox.setOrigin(m_designerUIBox.getSize().x / 2, m_designerUIBox.getSize().y / 2);
	m_designerUIBox.setPosition(window.getSize().x - (window.getSize().x / 20), window.getSize().y / 2);
	m_designerUIBox.setFillColor(sf::Color(150, 150, 150, 100));
	m_designerUIBox.setOutlineColor(sf::Color::Black);
	m_designerUIBox.setOutlineThickness(5.f);
	///shapes for use when designing a level and an semi-transparent shape is overlayed
	m_designerBar.setPosition(m_designerUIBox.getPosition().x, m_designerUIBox.getSize().y / 2);
	m_designerBar.setSize(sf::Vector2f(10.f, 100.f));
	m_designerBar.setOrigin(m_designerBar.getSize().x / 2, m_designerBar.getSize().y / 2);
	m_designerBar.setFillColor(sf::Color(0, 255, 0, 100));
	m_designerBarDefaultPosition = m_designerBar.getPosition();

	m_designerBox.setPosition(m_designerBar.getPosition().x, m_designerBar.getPosition().y - m_designerUIBox.getSize().y / 3);//not a used value yet
	m_designerBox.setSize(sf::Vector2f(50.f, 50.f));
	m_designerBox.setOrigin(m_designerBox.getSize().x / 2, m_designerBox.getSize().y / 2);
	m_designerBox.setFillColor(sf::Color(0, 255, 0, 100));
	m_designerBoxDefaultPosition = m_designerBox.getPosition();

	m_designerRamp.setPosition(m_designerBar.getPosition().x, m_designerBar.getPosition().y + m_designerUIBox.getSize().y / 3);//not a used value yet
	m_designerRamp.setPointCount(3);
	m_designerRamp.setPoint(0, sf::Vector2f(25, -25));// m_designerRamp.getPosition().x + 25, m_designerRamp.getPosition().y - 25));
	m_designerRamp.setPoint(1, sf::Vector2f(25, 25));// m_designerRamp.getPosition().x + 25, m_designerRamp.getPosition().y + 25));
	m_designerRamp.setPoint(2, sf::Vector2f(-25, 25));// m_designerRamp.getPosition().x - 25, m_designerRamp.getPosition().y + 25));
	m_designerRamp.setFillColor(sf::Color(0, 255, 0, 100));
	m_designerRampDefaultPosition = m_designerRamp.getPosition();
}

void UI::Update(b2Vec2 position, bool isMoving, int FPS)
{
	std::ostringstream fpsBuffer;
	fpsBuffer << FPS;
	m_FPSValue.setString((sf::String(fpsBuffer.str())));

	std::ostringstream posXBuffer;
	posXBuffer << int(m_convert->box2DXToCanvas(position.x));
	m_BallPositionValueX.setString(posXBuffer.str());
	
	std::ostringstream posYBuffer;
	posYBuffer << int(m_convert->box2DYToCanvas(position.y));
	m_BallPositionValueY.setString(posYBuffer.str());
	
	if (isMoving)
		m_StateValue.setString("Moving");
	else if (!isMoving)
		m_StateValue.setString("Stopped");
}

void UI::UpdateScreenPosition(sf::RenderWindow &window)
{
	///to change the position of the UI if/when the window is changed (fix visual errors)
}

void UI::SetVisibleDesignerShape(int shapeNum, bool visible)
{
	if (shapeNum == 0)
		m_drawRamp = visible;
	if (shapeNum == 1)
		m_drawBox = visible;
	if (shapeNum == 2)
		m_drawBar = visible;
}

void UI::SelectUIShape(sf::Vector2i mousePos)
{
	if (m_designerBar.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_selectedShape = CreateShape::ShapeType::Bar;
	}
	else if (m_designerBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_selectedShape = CreateShape::ShapeType::Box;
	}
	else if (m_designerRamp.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_selectedShape = CreateShape::ShapeType::Ramp;
	}
}

void UI::DeselectUIShape(bool createShape)
{
	if (createShape)
	{
		if (m_selectedShape == CreateShape::ShapeType::Bar)
		{ 
			b2PolygonShape tempShape;
			b2Vec2 * barPoints = new b2Vec2[m_designerBar.getPointCount()];
			sf::Transform tempTransform = m_designerBar.getTransform();
			for (int i = 0; i < m_designerBar.getPointCount(); i++)
			{
				sf::Vector2f tempVec = m_window->mapPixelToCoords(sf::Vector2i(tempTransform.transformPoint(m_designerBar.getPoint(i))));
				barPoints[i] = b2Vec2(m_convert->canvasXToBox2D(tempVec.x), 
					m_convert->canvasYToBox2D(tempVec.y));
			}
			tempShape.Set(barPoints, 4);
			b2FixtureDef tempFixDef = m_shape->setFixture(1, 1, 0);
			tempFixDef.shape = &tempShape;
			b2BodyDef tempBodyDef;
			tempBodyDef.type = b2BodyType::b2_staticBody;
			b2Body * tempBody = m_world->CreateBody(&tempBodyDef);
			tempBody->CreateFixture(&tempFixDef);
			m_level->PushStaticList(tempBody);
			ResetShapePos(CreateShape::ShapeType::Bar);

		}
		else if (m_selectedShape == CreateShape::ShapeType::Box)
		{
			b2PolygonShape tempShape;
			b2Vec2 * boxPoints = new b2Vec2[m_designerBox.getPointCount()];
			sf::Transform tempTransform = m_designerBox.getTransform();
			for (int i = 0; i < m_designerBox.getPointCount(); i++)
			{
				sf::Vector2f tempVec = m_window->mapPixelToCoords(sf::Vector2i(tempTransform.transformPoint(m_designerBox.getPoint(i))));
				boxPoints[i] = b2Vec2(m_convert->canvasXToBox2D(tempVec.x),
					m_convert->canvasYToBox2D(tempVec.y));
			}
			
			tempShape.Set(boxPoints, 4);
			b2FixtureDef tempFixDef = m_shape->setFixture(1, 1, 0);
			tempFixDef.shape = &tempShape;
			b2BodyDef tempBodyDef;
			tempBodyDef.type = b2BodyType::b2_staticBody;
			b2Body * tempBody = m_world->CreateBody(&tempBodyDef);
			tempBody->CreateFixture(&tempFixDef);
			m_level->PushStaticList(tempBody);
			ResetShapePos(CreateShape::ShapeType::Box);
		}
		else if (m_selectedShape == CreateShape::ShapeType::Ramp)
		{
			b2PolygonShape tempShape;
			b2Vec2 * rampPoints = new b2Vec2[m_designerRamp.getPointCount()];
			sf::Transform tempTransform = m_designerRamp.getTransform();
			for (int i = 0; i < m_designerRamp.getPointCount(); i++)
			{
				sf::Vector2f tempVec = m_window->mapPixelToCoords(sf::Vector2i(tempTransform.transformPoint(m_designerRamp.getPoint(i))));
				rampPoints[i] = b2Vec2(m_convert->canvasXToBox2D(tempVec.x),
					m_convert->canvasYToBox2D(tempVec.y));
			}
			tempShape.Set(rampPoints, 3);
			b2FixtureDef tempFixDef = m_shape->setFixture(1, 1, 0);
			tempFixDef.shape = &tempShape;
			b2BodyDef tempBodyDef;
			tempBodyDef.type = b2BodyType::b2_staticBody;
			b2Body * tempBody = m_world->CreateBody(&tempBodyDef);
			tempBody->CreateFixture(&tempFixDef);
			m_level->PushStaticList(tempBody);
			ResetShapePos(CreateShape::ShapeType::Ramp);
		}
	}
	m_selectedShape = CreateShape::ShapeType::None;
}

void UI::ResetShapePos(CreateShape::ShapeType shape)
{
	if (shape == CreateShape::ShapeType::Bar)
	{
		m_designerBar.setPosition(m_designerBarDefaultPosition);
		m_designerBar.setScale(1, 1);
		m_designerBar.setRotation(0);
	}
	else if (shape == CreateShape::ShapeType::Box)
	{
		m_designerBox.setPosition(m_designerBoxDefaultPosition);
		m_designerBox.setScale(1, 1);
		m_designerBox.setRotation(0);
	}
	else if (shape == CreateShape::ShapeType::Ramp)
	{
		m_designerRamp.setPosition(m_designerRampDefaultPosition);
		m_designerRamp.setScale(1, 1);
		m_designerRamp.setRotation(0);
	}
}

void UI::ToggleDrawDesignerUI()
{
	if (m_drawDesignerUI)
		m_drawDesignerUI = false;
	else
		m_drawDesignerUI = true;
	m_drawBox = m_drawDesignerUI;
	m_drawBar = m_drawDesignerUI;
	m_drawRamp = m_drawDesignerUI;
}

void UI::UpdateDesignerShapeScale(float scale)
{
	if (m_selectedShape == CreateShape::ShapeType::Bar)
	{
		//if the resulting shape is 0,0,0,0 don't allow the scale to happen
		if (sf::Vector2f(m_designerBar.getScale().x + scale, m_designerBar.getScale().y + scale) != sf::Vector2f(0, 0))
			m_designerBar.setScale(m_designerBar.getScale().x + scale, m_designerBar.getScale().y + scale);
	}
	if (m_selectedShape == CreateShape::ShapeType::Box)
	{
		if (sf::Vector2f(m_designerBox.getScale().x + scale, m_designerBox.getScale().y + scale) != sf::Vector2f(0, 0))
			m_designerBox.setScale(m_designerBox.getScale().x + scale, m_designerBox.getScale().y + scale);
	}
	if (m_selectedShape == CreateShape::ShapeType::Ramp)
	{
		if (sf::Vector2f(m_designerRamp.getScale().x + scale, m_designerRamp.getScale().y + scale) != sf::Vector2f(0, 0))
			m_designerRamp.setScale(m_designerRamp.getScale().x + scale, m_designerRamp.getScale().y + scale);
	}
}

void UI::RotateDesignerShape(float rotation)
{
	if (m_selectedShape == CreateShape::ShapeType::Bar)
		m_designerBar.setRotation(m_designerBar.getRotation() + rotation);
	
	if (m_selectedShape == CreateShape::ShapeType::Box)
		m_designerBox.setRotation(m_designerBox.getRotation() + rotation);

	if (m_selectedShape == CreateShape::ShapeType::Ramp)
		m_designerRamp.setRotation(m_designerRamp.getRotation() + rotation);
}

void UI::UpdateDesignerShape(float posX, float posY)
{
	if (m_selectedShape == CreateShape::ShapeType::Ramp)
	{
		m_designerRamp.setPosition(posX, posY);
	}

	if (m_selectedShape == CreateShape::ShapeType::Box)
	{
		m_designerBox.setPosition(posX, posY);
	}

	if (m_selectedShape == CreateShape::ShapeType::Bar)
	{
		m_designerBar.setPosition(posX, posY);
	}
}

void UI::UpdatePowerBar()
{
	if (alpha >= 250)
		powerBarUp = false;
	else if (alpha <= 0)
		powerBarUp = true;
	if (powerBarUp)
		alpha += 5;
	else
		alpha -= 5;
	m_PowerBarLevel.setFillColor(sf::Color(255, 0, 0, alpha));
}

int UI::ResetPowerBar()
{
	int getAlpha = alpha;
	alpha = 0;
	m_PowerBarLevel.setFillColor(sf::Color(255, 0, 0, alpha));
	return getAlpha;
}

void UI::setBallDirection(bool direction)
{
	m_arrowLeft = direction;
	if (m_arrowLeft)
		m_ArrowSprite.setTexture(m_leftArrowTexture);
	else
		m_ArrowSprite.setTexture(m_rightArrowTexture);
}

void UI::Draw(sf::RenderWindow & window)
{
	if (m_drawDesignerUI)
		window.draw(m_designerUIBox);
	if (m_drawBox)
		window.draw(m_designerBox);
	if (m_drawBar)
		window.draw(m_designerBar);
	if (m_drawRamp)
		window.draw(m_designerRamp);

	window.draw(m_UIBox);
	window.draw(m_FPSTitle);
	window.draw(m_FPSValue);
	window.draw(m_BallPositionTitle);
	window.draw(m_BallPositionTitleX);
	window.draw(m_BallPositionTitleY);
	window.draw(m_BallPositionValueX);
	window.draw(m_BallPositionValueY);
	window.draw(m_StateTitle);
	window.draw(m_StateValue);
	window.draw(m_arrowDirectionTitle);
	window.draw(m_ArrowSprite);
	window.draw(m_powerBarTitle);
	window.draw(m_PowerBarLevel);
}


UI::~UI()
{
}
