#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

//Including the Simple and Fast Multimedia Library
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Window
{	
public:

	Window();

	void updateWindow();

	void updateShapes();

	void renderWindow();

	//Create a uninitalized variable
	sf::RenderWindow mWindow;

	//Create a uninitalized variable
	sf::Event event;

	//Create a uninitalized variable
	sf::RectangleShape sPlayer;

	//Create a container for the shapes
	std::vector<sf::RectangleShape> shapes;

	float spawnTime = 40.0f;

	bool gameOver = false;

	bool menu = true;

private:

	void replayGame();

	bool doOnce = false;

	//Check collision between 2 shapes (playershape and colorshape)
	bool checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2);

	int screenWidth = 1000;
	int screenHeight = 1000;

	int maxHealth = 100;
	int currentHealth = maxHealth;

	int score = 0;

	bool anyKeyNotPressed();

	//UI FONT
	sf::Font headingFont;

	//UI TEXT
	sf::Text healthText;
	sf::Text scoreText;
	sf::Text endScoreText;
	sf::Text replayText;
	sf::Text menuText;
	sf::Text StartText;

};