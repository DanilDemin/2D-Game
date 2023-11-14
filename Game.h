#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>


#include "Player.h"
#include "SwagBall.h"




class Game {
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimmerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	 

public:
	Game();
	~Game();

	//Accessors

	const bool& getEndGame() const;

	//MOdifiers


	//Functions

	const bool running() const;
	void pollEvents();

	void spawnSwagsBalls();

	const int randBallType() const;
	void updatePLayer();
	void updateCollision();
	void updateGui();
	void update();


	void renderGui(sf::RenderTarget* targer);
	void render();

};