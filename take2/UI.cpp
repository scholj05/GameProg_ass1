#include "UI.h"



UI::UI(sf::RenderWindow &window, Conversion * convert)
{
	m_convert = convert;
	if (!m_font.loadFromFile("../resources/arial.ttf"))
	{
		std::cout << "Could not load arial.ttf font" << std::endl;
	}

	int charHeight, padding;
	m_UIBox.setSize(sf::Vector2f(float(window.getSize().x / 10), float(window.getSize().y)));
	m_UIBox.setOrigin(m_UIBox.getSize().x / 2, m_UIBox.getSize().y / 2);
	m_UIBox.setPosition(m_UIBox.getOrigin());
	m_UIBox.setFillColor(sf::Color(150, 150, 150, 100));
	m_UIBox.setOutlineColor(sf::Color::Black);
	m_UIBox.setOutlineThickness(5.f);
	
	charHeight = m_UIBox.getSize().x / 8;
	padding = charHeight / 2;

	int leftAlign = m_UIBox.getPosition().x - m_UIBox.getSize().x / 2 + padding;
	int rightAlign = m_UIBox.getPosition().x + charHeight + padding;

	m_FPSTitle.setCharacterSize(charHeight);
	m_FPSTitle.setPosition(leftAlign, 
		m_UIBox.getPosition().y - m_UIBox.getSize().y / 2 + padding);
	m_FPSTitle.setString(sf::String("FPS:"));
	m_FPSTitle.setFont(m_font);

	m_FPSValue.setCharacterSize(charHeight);
	m_FPSValue.setPosition(rightAlign,
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





	//m_PowerBarBackground.setPosition(m_UIBox.getSize().y / 2)

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
	else
		m_StateValue.setString("Eh b0ss, this is broken");
}

void UI::UpdateScreenPosition(sf::RenderWindow &window)
{

}

void UI::Draw(sf::RenderWindow & window)
{
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
}


UI::~UI()
{
}
