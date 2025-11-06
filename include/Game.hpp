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
	bool tryUpdateSnakeState();
	void updateSnakeDir(sf::Keyboard::Key keyPressed);
	void updateSnakeFace(std::string filePath);
	void drawObjects(sf::RenderWindow& window);
	void resetGame();
private:
	bool detectAppleCollision(sf::Vector2f nextHeadPos);
	bool detectGameOverCollision(sf::Vector2f nextHeadPos);
	void initBackgroundTexture(sf::RenderTexture& texture);
	void initFreeTiles();
	void growSnake(int numOfSegments);
	void occupyTile(int x, int y);
	void freeTile(int x, int y);
	sf::Vector2f getNextSnakeHeadPos();
	sf::Vector2f generateRandomFreeTilePos();

	int m_initSnakeTilePosX;
	int m_initSnakeTilePosY;

	Snake m_snake;
	Apple m_apple;

	// Vector of all currently free tiles
	std::vector<int> m_freeTiles; 
	// Indexes of all tiles within the freeTiles vector (occupied tiles have index -1)
	std::vector<int> m_posInFreeTiles; 

	sf::RenderTexture m_backgroundTexture;
	sf::Sprite m_background;

	ScoreCounter m_scoreCounter;
};
