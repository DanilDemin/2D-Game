#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game {
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	void initVariables();
	void initWindow();

public:
	Game();
	~Game();

	//Accessors


	//MOdifiers


	//Functions

	const bool running() const;
	void pollEvents();

	void update();
	void render();

};