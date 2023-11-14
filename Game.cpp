#include "Game.h"


void Game::initVariables()
{
	endGame = false;
	spawnTimmerMax = 10.f;
	spawnTimer = spawnTimmerMax;
	maxSwagBalls = 10;
	points = 0;
}

void Game::initWindow()
{
	videoMode = sf::VideoMode(1920, 1080);
	window = new sf::RenderWindow(videoMode, "Game 2",
		sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(90);
}

void Game::initFonts()
{
	if (font.loadFromFile("Fonts/Aller_Bd.ttf"))
	{
		std::cout << "Eror game init fonts" << '\n';
	}

}

void Game::initText()
{	
	//Gui text init
	guiText.setFont(font);
	guiText.setFillColor(sf::Color::White);
	guiText.setCharacterSize(60);

	//End game text
	endGameText.setFont(font);
	endGameText.setFillColor(sf::Color::White);
	endGameText.setCharacterSize(60);
	endGameText.setPosition(sf::Vector2f(20, 500));
	endGameText.setString("YOU ARE DEAD");
}

 

//Constructors and destructors
Game::Game()
{
	initWindow();
	initVariables();
	initFonts();
	initText();
}

Game::~Game()
{
	delete window;
}

const bool& Game::getEndGame() const
{
	return endGame;
}


//Functions

const bool Game::running() const
{
	return window->isOpen() /* && endGame == false*/ ;
}

void Game::pollEvents()
{
	while (window->pollEvent(sfmlEvent) )
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (sfmlEvent.key.code == sf::Keyboard::Escape) {
				window->close();
			}
			break;
		}

	}
}


//Functions
void Game::spawnSwagsBalls()
{
	//Timer
	if (spawnTimer < spawnTimmerMax)
	{
		spawnTimer += 1.f;
	}
	else 
	{
		if (swagBalls.size() < maxSwagBalls)
		{	
			swagBalls.push_back(SwagBall(*window,
					randBallType() ));
			spawnTimer = 0.f;
		}
		
	}
}

const int Game::randBallType() const
{	
	int type = SwagBallsTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
	{
		type = SwagBallsTypes::DAMAGING;
	}
	else if (randValue > 80 && randValue <= 100)
	{
		type = SwagBallsTypes::HEALING;
	}

	return 0;
}

void Game::updatePLayer()
{
	player.update(window);
	if (player.getHp() <= 0) { endGame = true; }

}

void Game::updateCollision()
{	
	//Check the collison

	for (size_t i = 0; i < swagBalls.size(); ++i)
	{
		if (player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds()))
		{	
			switch (swagBalls[i].getType())
			{
			case SwagBallsTypes::DEFAULT:
				++points;
				break;
			case SwagBallsTypes::DAMAGING:
				player.takeDamage(1);
				break;
			case SwagBallsTypes::HEALING:
				player.gainHealth(1);
				break;
			}

			//Add points
			

			//Remove the ball 
			swagBalls.erase(swagBalls.begin() + i);
			
		}
	}

	
}

void Game::updateGui()
{	
	std::stringstream ss;
	ss	<< "- Points: " << points << '\n' 
		<< "- Health: " << player.getHp() << " / " << player.getHpMax() << '\n';
	guiText.setString(ss.str());
}

void Game::update()
{
	pollEvents();

	if (endGame == false)
	{
		spawnSwagsBalls();
		updatePLayer();
		updateCollision();
		updateGui();
	}
}
	

void Game::renderGui(sf::RenderTarget* targer)
{
	targer->draw(guiText);
}

void Game::render()
{
	window->clear();

	//Render stuff
	player.render(window);

	for (auto i : swagBalls)
	{
		i.render(*window);
	}

	//Render gui
	renderGui(window);
	
	//Render end text 

	if (endGame == true)
	{
		window->draw(endGameText);
	}

	window->display();
}
