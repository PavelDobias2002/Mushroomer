// Name: Pavel Dobias
// Login: C00301332
// Date: 27/02/2024
// Approx hours of work : 15h
//---------------------------------------------------------------------------
//	Spring Interactive
/*
	Mushroomer:
	A player is a forager going to forest looking for mushrooms.
*/
// ---------------------------------------------------------------------------
// Known Bugs:
// When mushroom is picked and put inside the basket, it is possible to click at the location in which the mushroom was spawned and teleport it back
// When this happens it teleports the mushroom from the basket, this can be only seen when in basketView mode
// Mushrooms can spawn on each other creating bug, in which it is impossible to collect certain mushroom

#include "Mushroom.h"
#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{1000U, 600U}, "Mushroomer" },
	m_exitGame{false}
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupSound();	// load sound
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == event.type) //user pressed a key
		{
			processKeys(event);
		}
		if (sf::Event::MouseButtonPressed == event.type)	// user pressed mouse button
		{
			proccesMouseDown(event);
		}
		if (sf::Event::MouseMoved == event.type)	// user moves mouse
		{
			proccesMouseMove(event);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::D == t_event.key.code)	// D for debug mode
	{
		m_debugMode = !m_debugMode;
	}
	if (sf::Keyboard::B == t_event.key.code)	// B for basket mode
	{
		m_basketView = !m_basketView;
	}
}

void Game::proccesMouseDown(sf::Event t_event)
{
	
	m_mouseEnd.x = static_cast<float>(t_event.mouseButton.x);	// gets the end of mouse to location on x axis where user clicked
	m_mouseEnd.y = static_cast<float>(t_event.mouseButton.y);	// same but in y axis
	sf::Vector2f mushroomPosition;	// vector for muhsroomPosition
	
	if (m_basketView == false)	// if basket is not viewed
	{
		if (sf::Mouse::Left == t_event.mouseButton.button)	// if user presses left mouse
		{
			if (m_mushroomPicked == false)	// if mushroom is not picked already
			{
				for (int index = 0; index < MAX_MUSHROOMS; index++)	// loop trough the Mushrooms array
				{
					mushroomPosition = Mushrooms[index].getPosition();	// get position of the mushroom
					if (m_mouseEnd.x >= mushroomPosition.x && m_mouseEnd.x <= (mushroomPosition.x + 65.0f) &&
						m_mouseEnd.y >= mushroomPosition.y && m_mouseEnd.y <= (mushroomPosition.y + 65.0f))	// if the mouseEnd x and y position is same as the current mushrooms position 
					{
						std::cout << "mouse end works" << std::endl;

						m_mushroomPicked = true;	// mushroom is being picked
						m_currentIndex = index;		// gets the current index of mushrooms being picked
					}
				}
			}

		}
	}
	
}

void Game::proccesMouseMove(sf::Event t_event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);	// gets the position of the mouse

	if (m_mushroomPicked == true)	// is mushroom is picked
	{
			Mushrooms[m_currentIndex].setPosition(mousePosition.x, mousePosition.y);	// sets the position of current mushroom to the position of mouse
			m_mushroomSprite[m_currentIndex].setPosition(mousePosition.x, mousePosition.y);	// sets the mushroom sprite position to the mouse position everytime mouse moves
			
			if (mousePosition.y >= 450.0f && mousePosition.x <= 150.0f)	// if the location of the cursor is in the basket
			{
				// switch used to go trough the array of Mushrooms objects and position in the viewied basket
				// the size of viewed basket is 300, with one mushroom being 65 we add 8 on both sides, adding the more we add
				switch (m_currentIndex)
				{
					case 0:
						m_mushroomSprite[m_currentIndex].setPosition(158.0f, 231.0f);	// sets the position of the current mushroom in basket
						m_basketMushroom[m_currentIndex] = true;	// sets the true to bool, this means this mashroom is only drawn when in basket view
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 1:
						m_mushroomSprite[m_currentIndex].setPosition(231.0f, 231.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 2:
						m_mushroomSprite[m_currentIndex].setPosition(304.0f, 231.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 3:
						m_mushroomSprite[m_currentIndex].setPosition(158.0f, 304.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 4:
						m_mushroomSprite[m_currentIndex].setPosition(231.0f, 304.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 5:
						m_mushroomSprite[m_currentIndex].setPosition(304.0f, 304.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 6:
						m_mushroomSprite[m_currentIndex].setPosition(158.0f, 377.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 7:
						m_mushroomSprite[m_currentIndex].setPosition(231.0f, 377.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					case 8:
						m_mushroomSprite[m_currentIndex].setPosition(304.0f, 377.0f);
						m_basketMushroom[m_currentIndex] = true;
						m_mushroomPicked = false;	// mushroom is no longer picked
						break;
					default:
						break;
					
				}
			}
	}
}

void Game::update(sf::Time)
{
	if (m_exitGame == true)
	{
		m_window.close();
	}
	processEvents();
}

void Game::render()
{
	m_window.clear();
	if (m_debugMode)	// if debug mode is on
	{
		m_window.draw(m_forestBackground);
		m_window.draw(m_forestGround);
		m_window.draw(m_basket);
		for (int index = 0; index < 4; index++)	// loop for drawing the trees
		{
			m_window.draw(m_tree[index]);
		}
		for (int index = 0; index < MAX_MUSHROOMS; index++)	// loop for drawing the mushroom shapes
		{
			m_window.draw(Mushrooms[index].getShape());
			
		}
	}

	m_window.draw(m_forestBackgroundSprite);	//draws background and ground of forest and basket
	m_window.draw(m_forestGroundSprite);
	m_window.draw(m_basketSprite);

	for (int index = 0; index < 4; index++)	// loop for drawing the tree sprites
	{
		m_window.draw(m_treeSprite[index]);
	}
	for (int index = 0; index < MAX_MUSHROOMS; index++)
	{
		if (m_basketMushroom[index] == false)	// if this is false it means the mushroom is not in the basket
		{
			m_window.draw(m_mushroomSprite[index]);	// can be drawn on the forest ground
		}
	}
	if (m_basketView)	// if basket is viewed draw viewed basket
	{
		m_window.draw(m_viewBasket);	// draw viewed basket
		m_window.draw(m_viewBasketSprite);
		for (int index = 0; index < MAX_MUSHROOMS; index++)
		{
			m_window.draw(m_mushroomSprite[index]);	// draw mushroom sprites inside the basket
		}
	}
	m_window.draw(m_welcomeMessage);	//draw the message
	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONT\\CzechTales-Regular.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_welcomeMessage.setFont(m_font);
	m_welcomeMessage.setString("Pick up the mushrooms using LEFT mouse button and put them inside the basket");
	m_welcomeMessage.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(160.0f, 550.0f);
	m_welcomeMessage.setCharacterSize(25U);
	m_welcomeMessage.setOutlineColor(sf::Color::Black);
	m_welcomeMessage.setFillColor(sf::Color::Red);
	m_welcomeMessage.setOutlineThickness(3.0f);
}

void Game::setupSprite()
{
	if (!m_forestGroundTexture.loadFromFile("ASSETS\\forestground.png"))
	{
		std::cout << "problem loading ground" << std::endl;
	}
	m_forestGround.setSize(sf::Vector2f{ 1000.0f,350.0f });	// size for forest ground
	m_forestGround.setPosition(500.0f, 425.0f);	// sets position of the rectangle
	m_forestGround.setOrigin(500.0f, 175.0f);	// sets the origin in the middle of the rectangle
	m_forestGround.setFillColor(sf::Color::Red);
	m_forestGroundSprite.setTexture(m_forestGroundTexture);	// set texture position and origin of the ground, based on the rectangle
	m_forestGroundSprite.setPosition(500.0f, 425.0f);
	m_forestGroundSprite.setOrigin(500.0f, 175.0f);

	if (!m_forestBackgroundTexture.loadFromFile("ASSETS\\forestbackground.png"))
	{
		std::cout << "problem loading background" << std::endl;
	}
	m_forestBackground.setSize(sf::Vector2f{ 1000.0f,250.0f });	// size for forest ground
	m_forestBackground.setPosition(500.0f, 125.0f);	// sets position of the rectangle
	m_forestBackground.setOrigin(500.0f, 125.0f);	// sets the origin in the middle of the rectangle
	m_forestBackground.setFillColor(sf::Color::Blue);	
	m_forestBackgroundSprite.setTexture(m_forestBackgroundTexture); // set texture position and origin of the background, based on the rectangle
	m_forestBackgroundSprite.setPosition(500.0f, 125.0f);
	m_forestBackgroundSprite.setOrigin(500.0f, 125.0f);

	
	if (!m_treeTexture[0].loadFromFile("ASSETS\\trees1.png"))
	{
		std::cout << "problem loading tree 0" << std::endl;
	}
	m_tree[0].setSize(sf::Vector2f{ 108.0f,400.0f });	// set size, texture and position of the first tree
	m_tree[0].setPosition(m_treePosition.x, m_treePosition.y);
	m_treeSprite[0].setTexture(m_treeTexture[0]);
	m_treeSprite[0].setPosition(m_treePosition.x, m_treePosition.y);

	if (!m_treeTexture[1].loadFromFile("ASSETS\\trees2.png"))
	{
		std::cout << "problem loading tree 1" << std::endl;
	}
	m_tree[1].setSize(sf::Vector2f{ 108.0f,400.0f });	// set size, texture and position of the second tree
	m_tree[1].setPosition(m_treePosition.x + 200.0f, m_treePosition.y - 80.0f);
	m_treeSprite[1].setTexture(m_treeTexture[1]);
	m_treeSprite[1].setPosition(m_treePosition.x + 200.0f, m_treePosition.y - 80.0f);

	if (!m_treeTexture[2].loadFromFile("ASSETS\\trees3.png"))
	{
		std::cout << "problem loading tree 2" << std::endl;
	}
	m_tree[2].setSize(sf::Vector2f{ 108.0f,400.0f });	// set size, texture and position of the third tree
	m_tree[2].setPosition(m_treePosition.x + 600.0f, m_treePosition.y - 50.0f);
	m_treeSprite[2].setTexture(m_treeTexture[2]);
	m_treeSprite[2].setPosition(m_treePosition.x + 600.0f, m_treePosition.y - 50.0f);

	if (!m_treeTexture[3].loadFromFile("ASSETS\\trees4.png"))
	{
		std::cout << "problem loading tree 3" << std::endl;
	}
	m_tree[3].setSize(sf::Vector2f{ 108.0f,400.0f });	// set size, texture and position of the forth tree
	m_tree[3].setPosition(m_treePosition.x + 800.0f, m_treePosition.y);
	m_treeSprite[3].setTexture(m_treeTexture[3]);
	m_treeSprite[3].setPosition(m_treePosition.x + 800.0f, m_treePosition.y);

	if (!m_basketTexture.loadFromFile("ASSETS\\basket.png"))
	{
		std::cout << "problem loading basket" << std::endl;
	}
	m_basket.setPosition(0.0f, 450.0f);	// set position of the basket in left down corner
	m_basket.setSize(sf::Vector2f{ 150.0f, 150.0f });	// set size of basket
	m_basket.setFillColor(sf::Color::Black);
	m_basketSprite.setTexture(m_basketTexture);	// set the texture and position for basket
	m_basketSprite.setPosition(0.0f, 450.0f);

	if (!m_viewBasketTexture.loadFromFile("ASSETS\\basketviewed.png"))
	{
		std::cout << "problem with viewed basket" << std::endl;
	}
	m_viewBasket.setPosition(150.0f, 223.0f);	// set position of the viewed basket on top of the right corner of the normal basket
	m_viewBasket.setSize(sf::Vector2f{ 227.0f, 227.0f });	// set size of viewed basket
	m_viewBasket.setFillColor(sf::Color::Black);
	m_viewBasketSprite.setTexture(m_viewBasketTexture);	// set texture and position for viewed basket
	m_viewBasketSprite.setPosition(150.0f, 223.0f);

	// loading textures on mushroom sprite
	for (int index = 0; index < MAX_MUSHROOMS; index++) // goes trough all the mushrooms
	{
		if (index == 0)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[0].loadFromFile("ASSETS\\hribpixel.png"))
			{
				std::cout << "problem loading texture 0" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[0]);	// sets texture, position for the mushroom
			m_mushroomPos = Mushrooms[index].getPosition();	// gets the position of the mushroom so the sprite can be located in the same pos
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 1)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[1].loadFromFile("ASSETS\\muchomurka.png"))
			{
				std::cout << "problem loading texture 1" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[1]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 2)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[2].loadFromFile("ASSETS\\bedle.png"))
			{
				std::cout << "problem loading texture 2" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[2]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 3)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[3].loadFromFile("ASSETS\\kuratka.png"))
			{
				std::cout << "problem loading texture 3" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[3]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 4)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[4].loadFromFile("ASSETS\\babka.png"))
			{
				std::cout << "problem loading texture 4" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[4]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 5)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[5].loadFromFile("ASSETS\\satanhrib.png"))
			{
				std::cout << "problem loading texture 5" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[5]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 6)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[6].loadFromFile("ASSETS\\muchomurkazelena.png"))
			{
				std::cout << "problem loading texture 6" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[6]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 7)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[7].loadFromFile("ASSETS\\lysohlavky.png"))
			{
				std::cout << "problem loading texture 7" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[7]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		if (index == 8)	// if its the first position etc. loads the texture on that sprite
		{
			if (!m_mushroomTexture[8].loadFromFile("ASSETS\\prasivka.png"))
			{
				std::cout << "problem loading texture 8" << std::endl;
			}
			m_mushroomSprite[index].setTexture(m_mushroomTexture[8]);
			m_mushroomPos = Mushrooms[index].getPosition();
			m_mushroomSprite[index].setPosition(m_mushroomPos);
		}
		
	}
}

void Game::setupSound()
{
	if (!m_bufferForest.loadFromFile("ASSETS\\AUDIO\\forestsound.wav"))
	{
		std::cout << "problem with audio" << std::endl;
	}
	m_soundForest.setBuffer(m_bufferForest);
	m_soundForest.play();
}
