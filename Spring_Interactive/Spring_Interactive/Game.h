/// <summary>
/// author Pavel Dobias 2024
/// Login: C00301332
/// Spring Interactive: Mushroomer
/// </summary>
#ifndef GAME
#define GAME

#include "Mushroom.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int MAX_MUSHROOMS = 9;	// global for max mushrooms in array


class Game
{
public:
	Game();
	void run();
	Mushroom Mushrooms[MAX_MUSHROOMS];	// array consiting of 5 mushroom objects
private:
	void processEvents();
	void processKeys(sf::Event t_event);	// function proccesing pressed keys
	void proccesMouseDown(sf::Event t_event);	// function procces pressed mouse buttons
	void proccesMouseMove(sf::Event t_event);	// function proccesing moving mouse
	void update(sf::Time);
	void render();

	bool m_exitGame;	
	bool m_debugMode;	// bool for debug mode
	bool m_mushroomPicked{ false };
	int m_currentIndex;	// int for current index
	

	void setupFontAndText();
	void setupSprite();
	void setupSound();

private:
	sf::RenderWindow m_window;

	sf::Sound m_soundForest;	// Sound and buffer used for forest audio
	sf::SoundBuffer m_bufferForest;

	sf::Font m_font;		// font used for messages
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Sprite m_treeSprite[4];	// sprite and texture for trees
	sf::Texture m_treeTexture[4];	
	sf::RectangleShape m_tree[4];	// array with trees

	sf::RectangleShape m_forestGround;	// two rectangles dividing screen into ground and background
	sf::Sprite m_forestGroundSprite;	// sprite and texture for ground
	sf::Texture m_forestGroundTexture;

	sf::RectangleShape m_forestBackground;	// sprite and texture for background
	sf::Sprite m_forestBackgroundSprite;
	sf::Texture m_forestBackgroundTexture;
	
	sf::Vector2f m_treePosition{ 50.0f, 0.0f };	// position of first tree used to set other trees

	sf::Vector2f m_mouseEnd;	// vector for where mouse is when clicked

	sf::RectangleShape m_basket;	// shape, sprite and texture for basket
	sf::Sprite m_basketSprite;
	sf::Texture m_basketTexture;

	sf::RectangleShape m_viewBasket;	// shape, sprite and texture for basket when its viewed
	sf::Sprite m_viewBasketSprite;
	sf::Texture m_viewBasketTexture;
	bool m_basketView{ false };	// if true basket view is shown

	sf::Sprite m_mushroomSprite[MAX_MUSHROOMS];	// array of sprites and textures for mushrooms
	sf::Texture m_mushroomTexture[MAX_MUSHROOMS];
	sf::Vector2f m_mushroomPos;	// variable for mushroom position
	bool m_basketMushroom[MAX_MUSHROOMS]{false};	// variable for when mushroom is in basket
	
};

#endif // !GAME