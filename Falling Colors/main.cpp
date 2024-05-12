//Including the window header file
#include "window.h"


//Creating Struct for all the colors
struct colors
{
	sf::Color color;
};

//Creating a player object
class Player
{
public:

	Player();

	int points = 0;

	sf::RectangleShape sPlayer;
};


//Creating a color object
class Color
{
public:

	Color();

	void spawnColorTimer();

private:

	void spawnColor();

	colors index[5];

	float timer = 0.0f;
};




//Construct the classes
Window window;
Player player;
Color color;

int main()
{

	//Seeding the random number generator
	srand(static_cast<unsigned int>(time(0)));

	//Implementing a fixed timestep gameloop
	sf::Clock timeClock;
	float frameTime = 1.0/60.0f;
	float updates = 0;


	//Implementing the game loop
	while (window.mWindow.isOpen())
	{
		updates += timeClock.getElapsedTime().asSeconds();
		timeClock.restart();

		if (updates >= frameTime)
		{
			window.updateWindow();

			window.renderWindow();

			//Check if the game is not over or if the start menu isn't on
			if (!window.gameOver && !window.menu)
			{
				color.spawnColorTimer();

				window.updateShapes();
			}

			updates -= frameTime;

		}
	}


	return 0;
}


Player::Player()
{
	//Set player size
	sPlayer.setSize(sf::Vector2f(100.0f, 100.0f));

	//Set player color
	sPlayer.setFillColor(sf::Color::White);

	//Set player origin to the midde
	sPlayer.setOrigin(sPlayer.getSize().x / 2, sPlayer.getSize().y / 2);

	//Set player position to the middle of the screen and the lowest border
	sPlayer.setPosition(window.mWindow.getSize().x / 2, window.mWindow.getSize().y - sPlayer.getSize().y);

	window.sPlayer = sPlayer;
}

Color::Color()
{
	index[0].color = sf::Color::Blue;
	index[1].color = sf::Color::Green;
	index[2].color = sf::Color::Yellow;
	index[3].color = sf::Color::Magenta;
	index[4].color = sf::Color::Red;
}

void Color::spawnColorTimer()
{
	//Implementing a timer
	timer += 1;

	if (timer >= window.spawnTime)
	{
		timer = 0;
		spawnColor();
		if (window.spawnTime > 10)
		{
			window.spawnTime -= 0.1f;
		}
	}
}

void Color::spawnColor()
{
	//Creating a simple shape
	sf::RectangleShape shape(sf::Vector2f(100, 100));

	//Set the shape origin to its middle
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);

	//Set a random x position for the shape
	shape.setPosition(rand() % 851 + 50, -100);

	//Get a random index and assign a color given to that index
	shape.setFillColor(index[rand() % 5].color);

	//Add a shape to the vector container
	window.shapes.push_back(shape);
}



