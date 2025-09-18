#pragma once  

#include <SFML/Graphics.hpp>  
#include <random>

#include "../includes/Utils.hpp"
#include "../includes/Snake.hpp"  
#include "../includes/Apple.hpp"  
#include "../includes/Tile.hpp"  
#include "../includes/PauseMenu.hpp"
#include "../includes/GameOverMenu.hpp"

class Game {
public:
	Game();
	std::map<char, int> getMapSizeInTiles() const;
	void drawGameObjects(sf::RenderWindow& window);
	void forwardSnakeInput(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void resetGame();
	sf::Vector2f getNextSnakeHeadTilePos();
	bool detectAppleCollision(sf::Vector2f nextHeadPos);
	bool detectGameOverCollision(sf::Vector2f nextHeadPos);
	bool tryUpdateSnakeState();
	sf::Vector2f generateRandomFreeTilePos();
	
	// Tile management
	void occupyTile(int x, int y);
	void freeTile(int x, int y);

private:

	static constexpr int initSnakeTilePosX = 2;
	static constexpr int initSnakeTilePosY = 2;
	const sf::Color colorTile1;
	const sf::Color colorTile2;

	// Game background  
	sf::RenderTexture texture;
	sf::Sprite background;

	// Game objects  
	Apple apple;
	Snake snake;

	// Tiles  
	// REMOVE TILES ARRAY?
	Tile tiles[Utils::mapSizeInTilesX][Utils::mapSizeInTilesY];

	std::vector<int> freeTiles;
	std::vector<int> posInFreeTiles;

	/*
		- freeTiles: Vector of all currently free tiles
		- posInFreeTiles: The positions of all tiles within the freeTiles vector (non-free tiles have value -1)

	*/
};
