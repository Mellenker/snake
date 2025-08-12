#pragma once  

#include <SFML/Graphics.hpp>  

#include "includes/Utils.hpp"
#include "includes/Snake.hpp"  
#include "includes/Apple.hpp"  
#include "includes/Tile.hpp"  
#include "includes/PauseMenu.hpp"
#include "includes/GameOverMenu.hpp"

class Game {
public:
	Game();
	std::map<char, int> getMapSizeInTiles() const;
	void drawGameObjects(sf::RenderWindow& window);
	void forwardSnakeInput(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void resetGame();
	sf::Vector2i getNextSnakeHeadTilePos();
	bool detectAppleCollision(sf::Vector2i nextHeadPos);
	bool detectGameOverCollision(sf::Vector2i nextHeadPos);
	bool tryUpdateSnakeState();
private:

	static constexpr int initPosX = 1;
	static constexpr int initPosY = 1;
	const sf::Color colorTile1;
	const sf::Color colorTile2;

	// Game background  
	sf::RenderTexture texture;
	sf::Sprite background;

	// Game objects  
	Apple apple;
	Snake snake;

	// Tiles  
	Tile tiles[Utils::mapSizeInTilesX][Utils::mapSizeInTilesY];
};
