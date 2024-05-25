/// <summary>
/// author Pavel Dobias 2024
/// Login: C00301332
/// Spring Interactive: Mushroomer
/// </summary>

#include "Mushroom.h"
#include <random>  // for randomazing

Mushroom::Mushroom()	// default constructor
{
	loadMushroom();	// call function which loads the mushroom 
	setPosition();	// call function which sets randomly position for the mushroom
}

void Mushroom::loadMushroom()
{
	float red;
	float green;
	float blue;
	// sets random color for mushroomShape
	red = (rand() % 255) + 1;
	blue = (rand() % 255) + 1;
	green = (rand() % 255) + 1;
	
	m_mushroomShape.setSize(m_mushroomSize);	// size of mushroomShape
	m_mushroomShape.setFillColor(sf::Color(red, green, blue));	// sets the color
}

sf::RectangleShape Mushroom::getShape()
{
	return m_mushroomShape;	// return mushroom shape
}

sf::Vector2f Mushroom::setPosition()
{
	srand(time(NULL) + rand());	// seed for random numbers

	m_posMushroom.x = (rand() % 650) + 150;	// randomly generates position in x and y axis
	m_posMushroom.y = (rand() % 100) + 350;
	setPosition(m_posMushroom.x, m_posMushroom.y);

	return m_posMushroom;	// return the position
}

void Mushroom::setPosition(int xPos, int yPos)
{
	m_mushroomShape.setPosition(xPos, yPos);
}

sf::Vector2f Mushroom::getPosition()
{
	return sf::Vector2f(m_posMushroom);	// returns just the position of the mushroom
}




