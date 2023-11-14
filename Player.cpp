#include "Player.h"

void Player::initVariables()
{
	movementSpeed = 10.f;
	hpMax = 10;
	hp = hpMax;
	points = 0;
}

void Player::initShape()
{
	shape.setFillColor(sf::Color::Red);
	shape.setSize(sf::Vector2f(100.f, 100.f));
}

Player::Player(float x, float y)
{	
	shape.setPosition(x, y);

	initVariables();
	initShape();
}

Player::~Player()
{
}

//Accesors
const sf::RectangleShape& Player::getShape() const
{
	return shape;
}

const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}


//Functions
void Player::takeDamage(const int damage)
{
	if (hp > 0)
	{
		hp -= damage;
	}

	if (hp < 0)
	{
		hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (hp < hpMax)
	{
		hp += health;
	}

	if (hp > hpMax)
	{
		hp = hpMax;
	}
}


void Player::updateInput()
{
	//Keyboard	input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move(movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0.f, -movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0.f, movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (shape.getGlobalBounds().left <= 0.f)
	{
		shape.setPosition(0.f, shape.getGlobalBounds().top);
	}
	//Right
	if (shape.getGlobalBounds().left
		+ shape.getGlobalBounds().width >= target->getSize().x)
	{
		shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);
	}

	//Top
	if (shape.getGlobalBounds().top <= 0)
	{
		shape.setPosition(shape.getGlobalBounds().left, 0.f);
	}
	//Bottom
	if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y)
	{
		shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);
	}
	
}

void Player::update(const sf::RenderTarget* target)
{
	updateInput();

	//Window bounds colisions

	updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
	
