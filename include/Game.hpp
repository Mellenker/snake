#pragma once  

#include <SFML/Graphics.hpp>  
#include <random>

#include "Utils.hpp"
#include "Snake.hpp"  
#include "Apple.hpp"  
#include "Colors.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "ScoreCounter.hpp"

class Game {
public:
	Game();
	void drawObjects(sf::RenderWindow& window);
	void forwardSnakeInput(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void resetGame();
	bool detectAppleCollision(sf::Vector2f nextHeadPos);
	bool detectGameOverCollision(sf::Vector2f nextHeadPos);
	bool tryUpdateSnakeState();
	void initializeFreeTiles();
	sf::Vector2f getNextSnakeHeadPos();
	sf::Vector2f generateRandomFreeTilePos();
	
	// Tile management
	void occupyTile(int x, int y);
	void freeTile(int x, int y);

private:

	int initSnakeTilePosX;
	int initSnakeTilePosY;

	Snake snake;
	Apple apple;

	std::vector<int> freeTiles; // Vector of all currently free tiles
	std::vector<int> posInFreeTiles; // Indexes of all tiles within the freeTiles vector (occupied tiles have index -1)

	sf::RenderTexture texture;
	sf::Sprite background;

	ScoreCounter scoreCounter;

};
