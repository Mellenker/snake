#pragma once  

#include <SFML/Graphics.hpp>  
#include <random>

#include "../includes/Utils.hpp"
#include "../includes/Snake.hpp"  
#include "../includes/Apple.hpp"  
#include "../includes/Tile.hpp"  
#include "../includes/PauseMenu.hpp"
#include "../includes/GameOverMenu.hpp"
#include "../includes/ScoreCounter.hpp"

class Game {
public:
	Game();
	std::map<char, int> getMapSizeInTiles() const;
	void drawObjects(sf::RenderWindow& window);
	void forwardSnakeInput(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void resetGame();
	bool detectAppleCollision(sf::Vector2f nextHeadPos);
	bool detectGameOverCollision(sf::Vector2f nextHeadPos);
	bool tryUpdateSnakeState();

	sf::Vector2f getNextSnakeHeadPos();
	sf::Vector2f generateRandomFreeTilePos();
	
	// Tile management
	void occupyTile(int x, int y);
	void freeTile(int x, int y);

private:

	static constexpr int initSnakeTilePosX = 2;
	static constexpr int initSnakeTilePosY = 2;
	const sf::Color colorTile1;
	const sf::Color colorTile2;


	sf::RenderTexture texture;
	sf::Sprite background;

	ScoreCounter scoreCounter;

	Apple apple;
	Snake snake;

	std::vector<int> freeTiles; // Vector of all currently free tiles
	std::vector<int> posInFreeTiles; // Indexes of all tiles within the freeTiles vector (occupied tiles have index -1)
};
