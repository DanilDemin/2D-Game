#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderWindow& window)
{
	shape.setRadius(static_cast<float>(rand() % 50 + 25));
	
	sf::Color color;

	switch (type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(2.f);
		break;
	}

	
	shape.setFillColor(color);
	shape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % window.getSize().x - shape.getGlobalBounds().width),
			static_cast<float>(rand() % window.getSize().y - shape.getGlobalBounds().height))
		);
}

SwagBall::SwagBall(const sf::RenderWindow& window, int type)
	: type(type)
{	
	initShape(window);
}

SwagBall::~SwagBall()
{
}

const sf::CircleShape SwagBall::getShape() const
{
	return shape;
}

const int& SwagBall::getType() const
{
	return type;
	// TODO: insert return statement here
}

void SwagBall::update()
{
}

void SwagBall::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
