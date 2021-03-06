// catchGame.cpp : Defines the entry point for the console application.
//

// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 


sf::RectangleShape drawGrid(int length, int r, int c);
sf::RectangleShape drawSquare(int length, int posX, int posY);
void drawLine(sf::RenderWindow &window);
sf::RectangleShape  drawPixel(int x, int y, int length);

int main()
{



	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "First Graphics in C++");
	//do this once to "seed" the random number generator
	srand(time(NULL));

	float randomNum;

	// Example generate  number between 0 and 749

	randomNum = rand() % 750 + 0;


	// setup any shapes or variables.

	sf::CircleShape player(30);
	sf::CircleShape apple(50);

	float appleSpeed = 2;

	player.setFillColor(sf::Color::Red);

	player.setPosition(200, 550);


	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();			
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{


			// get keyboard input.

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player.move(-1, 0);

				
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.move(1, 0);
			}

			apple.move(0, appleSpeed);



			if (player.getPosition().x < 0)
			{
				player.setPosition(800 - player.getRadius() * 2, player.getPosition().y);
			}
			
			if (apple.getPosition().y > 600)
			{
				appleSpeed = appleSpeed + 1;
				randomNum = rand() % 750 + 0;
				apple.setPosition(randomNum, 0);
			}
			if (apple.getGlobalBounds().intersects(player.getGlobalBounds()))
			{

				player.setFillColor(sf::Color::Blue);
			}
	
			//clear the screen and draw the shapes.
			window.clear();
			for (int r = 0; r < 60; r++)
			{
				for (int c = 0; c < 60; c++)
				{
					window.draw(drawGrid(20, r, c));
				}
			}
			//window.draw(player);
			//window.draw(apple);
			drawLine(window);
			//tell SFML  to display everything 
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

//draws the grid (calls each sqaure)
sf::RectangleShape drawGrid(int length, int r, int c)
{
	return drawSquare(length,r,c); //return shape to draw
}

//draws a square
sf::RectangleShape drawSquare(int length, int posX, int posY)
{
	//setup
	sf::RectangleShape square;
	square.setSize(sf::Vector2f(length, length));
	//outline
	square.setOutlineColor(sf::Color::Green);
	square.setOutlineThickness(1);
	posX = posX * length;
	posY = posY * length;
	square.setPosition(posX, posY);
	return square; //return
}

//draw the line
void drawLine(sf::RenderWindow &window)
{
	sf::Mouse::getPosition();
 	int x1 = 20;
	int y1 = 12;
	int x2 = sf::Mouse::getPosition().x;
	int y2 = sf::Mouse::getPosition().y;
	x2 /= 34;
	y2 /= 34;

	int deltax = abs(x2 - x1);
	int deltay = abs(y2 - y1);
	int error = 0;
	int Xgradient = deltay;

	int y = y1;
	if (x1 < x2)
	{
		for (int x = x1; x < x2; x++)
		{
			window.draw(drawPixel(x, y, 20));
			error = error + Xgradient;
			if (2 * error >= deltax)
			{
				y = y + 1;
				error = error - deltax;
				//1 * deltax;
			}
		}
	}
	//else if (y1 > y2)
	//{
	//	for (int x = x1; x > x2; x++)
	//	{
	//		window.draw(drawPixel(x, y, 20));
	//		error = error + Xgradient;
	//		if (2 * error >= deltax)
	//		{
	//			y = y - 1;
	//			error = error - deltax;
	//			//1 * deltax;
	//		}
	//	}
	//}
	//else if (y2 < y1)
	//{
	//	for (int x = x1; x > x2; x++)
	//	{
	//		window.draw(drawPixel(x, y, 20));
	//		error = error + Xgradient;
	//		if (2 * error >= deltax)
	//		{
	//			y = y + 1;
	//			error = error - deltax;
	//			//1 * deltax;
	//		}
	//	}
	//}

}

//draw pixel (line)
sf::RectangleShape drawPixel(int x, int y, int length)
{
	
	sf::RectangleShape square;
	square.setSize(sf::Vector2f(length, length));
	//outline
	square.setFillColor(sf::Color::Red);
	x = x * length;
	y = y * length;
	square.setPosition(x, y);
	
	return square;
}
