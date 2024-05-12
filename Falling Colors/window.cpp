#include "window.h"

Window::Window()
{
	//Initialize font
	headingFont.loadFromFile("Assets/04b.ttf");

	//Initialize and set the healthText
	healthText.setFont(headingFont);
	healthText.setString("HP " + std::to_string(currentHealth));
	healthText.setCharacterSize(60);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(675, 0);

	//Initialize and set the scoreText
	scoreText.setFont(headingFont);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::White);

	//Initialize and set the endScoreText
	endScoreText.setFont(headingFont);
	endScoreText.setString(std::to_string(score));
	endScoreText.setCharacterSize(60);
	endScoreText.setFillColor(sf::Color::White);
	endScoreText.setPosition(450, 500);

	//Initialize and set the replayText
	replayText.setFont(headingFont);
	replayText.setString("Press any key to play again");
	replayText.setCharacterSize(30);
	replayText.setFillColor(sf::Color::White);
	replayText.setPosition(150, 700);

	//Initialize and set the menuText
	menuText.setFont(headingFont);
	menuText.setString("Falling Colors");
	menuText.setCharacterSize(70);
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition(100, 400);

	//Initialize and set the StartText
	StartText.setFont(headingFont);
	StartText.setString("Press any key to play");
	StartText.setCharacterSize(30);
	StartText.setFillColor(sf::Color::White);
	StartText.setPosition(225, 500);

	//Creating the window
	mWindow.create(sf::VideoMode(screenWidth, screenHeight), "Falling Colors");
}

void Window::updateWindow()
{

	sf::Event event;

	while (mWindow.pollEvent(event))
	{

		//Detect if window is getting closed
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		//Detect if keyboard input Esc is pressed, if true close the window
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			mWindow.close();
		}


		//Detect if keyboard input A is pressed, if true then move player +100 on the X
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
		{
			sPlayer.move(100, 0);

			//Detect if player is out of screen if yes, set player on the other side of the screen
			if (sPlayer.getPosition().x > mWindow.getSize().x)
			{
				sPlayer.setPosition(0, mWindow.getSize().y - sPlayer.getSize().y);
			}
		}

		//Detect if keyboard input A is pressed, if true then move player -100 on the X
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			sPlayer.move(-100, 0);

			//Detect if player is out of screen if yes, set player on the other side of the screen
			if (sPlayer.getPosition().x < 0)
			{
				sPlayer.setPosition(mWindow.getSize().x, mWindow.getSize().y - sPlayer.getSize().y);
			}
		}

	}
}

void Window::updateShapes()
{
	//Check if the shapes container is not empty
	if (!shapes.empty())
	{
		//For each shape in the container we want to move the shape downwards
		for (int i = 0; i < shapes.size(); i++)
		{
			//Move the shape with 20 on Y axis
			shapes[i].move(0, 20);

			//Check if the player is colliding with a shape, if yes increase score
			if (checkCollision(sPlayer, shapes[i]))
			{
				shapes.erase(shapes.begin());
				score += 1;
				scoreText.setString(std::to_string(score));
			}

			//Check if the shape is out of screen, if yes do damage
			if (shapes[i].getPosition().y > 1000 + 50)
			{
				shapes.erase(shapes.begin());
				currentHealth -= 10;
				healthText.setString("HP " + std::to_string(currentHealth));
				if (currentHealth <= 0)
				{
					gameOver = true;
				}
			}

		}
	}
}

void Window::renderWindow()
{

	//Clearing the window
	mWindow.clear();

	//Check if menu is true
	if (menu)
	{
		//Drawing on the window
		mWindow.draw(menuText);

		//Drawing on the window
		mWindow.draw(StartText);

		menu = anyKeyNotPressed();
	}
	//Check if gameover is true
	else if (gameOver)
	{
		//Drawing on the window
		mWindow.draw(endScoreText);
		//Drawing on the window
		mWindow.draw(replayText);

		replayGame();

		gameOver = anyKeyNotPressed();
	}
	//If both of the if statements are false then we are in the main game loop
	else
	{
		//Drawing on the window
		mWindow.draw(healthText);

		//Drawing on the window
		mWindow.draw(scoreText);

		//Drawing on the window
		mWindow.draw(sPlayer);

		//Check if the shapes container is not empty
		if (!shapes.empty())
		{
			//For each shape in the container we draw the shape
			for (int i = 0; i < shapes.size(); i++)
			{
				mWindow.draw(shapes[i]);
			}
		}
	}

	//Displaying the window
	mWindow.display();
}

void Window::replayGame()
{
	//When game is over reset all the variables and UI's
	if (doOnce == false)
	{
		doOnce = true;
		endScoreText.setString(std::to_string(score));
		spawnTime = 40.0f;
		currentHealth = 100;
		healthText.setString("HP " + std::to_string(currentHealth));
		score = 0;
		scoreText.setString(std::to_string(score));
		shapes.clear();
	}
}

bool Window::checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2)
{
	//Get the size in float of the 2 given parameters
	sf::FloatRect size1 = shape1.getGlobalBounds();
	sf::FloatRect size2 = shape2.getGlobalBounds();

	if (size1.intersects(size2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Window::anyKeyNotPressed()
{
	//Check if the player is pressing a key
	for (int i = -1; i < sf::Keyboard::KeyCount; i++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			doOnce = false;
			return false;
		}
	}
	return true;
}
