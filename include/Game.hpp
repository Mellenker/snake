#pragma once  
#include <SFML/Graphics.hpp>  
#include "Snake.hpp"  
#include "Apple.hpp"  
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "ScoreCounter.hpp"

class Game {
public:
	Game();
	void drawObjects(sf::RenderWindow& window);
	void updateSnakeDir(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void resetGame();
	bool detectAppleCollision(sf::Vector2f nextHeadPos);
	bool detectGameOverCollision(sf::Vector2f nextHeadPos);
	bool tryUpdateSnakeState();
	void initializeFreeTiles();
	void growSnake();
	void updateSnakeFace(std::string filePath);
	sf::Vector2f getNextSnakeHeadPos();
	sf::Vector2f generateRandomFreeTilePos();
	
	// Tile management
	void occupyTile(int x, int y);
	void freeTile(int x, int y);

private:
	int m_initSnakeTilePosX;
	int m_initSnakeTilePosY;

	Snake m_snake;
	Apple m_apple;

	std::vector<int> m_freeTiles; // Vector of all currently free tiles
	std::vector<int> m_posInFreeTiles; // Indexes of all tiles within the freeTiles vector (occupied tiles have index -1)

	sf::RenderTexture m_texture;
	sf::Sprite m_background;

	ScoreCounter m_scoreCounter;
};
