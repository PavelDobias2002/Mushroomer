/// <summary>
/// author Pavel Dobias 2024
/// Login: C00301332
/// Spring Interactive: Mushroomer
/// </summary>

// Mushroom class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // for randomazing

class Mushroom
{
	// private:
	sf::RectangleShape m_mushroomShape;	// rectangle on which sprite will load
	
public:
	Mushroom(); // default constructor

	sf::Vector2f m_mushroomSize{ 65.0f,65.0f };	// size for mushroom

	void loadMushroom();	// function loading mushroom
	sf::RectangleShape getShape();	// function to return mushroom shape

	sf::Vector2f m_posMushroom;	// vector2f for position
	void setPosition(int xPos, int yPos);	// function for mushroom positions
	sf::Vector2f setPosition();	// function randomly generating mushroom positions
	sf::Vector2f getPosition();	// function just getting the curent mushroom position
};