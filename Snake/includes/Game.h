#pragma once

#include <SFML/Graphics.hpp>

#include "includes/Snake.h"
#include "includes/Apple.h"
#include "includes/Tile.h"'
#include "includes/Menu.h"

class Game {
public:
	Game();
	std::map<char, int> getMapSizeInTiles() const;
	void drawGameObjects(sf::RenderWindow& window);
	void handleKeyboardInput(sf::Keyboard::Key keyPressed);
	void spawnTiles(sf::RenderTexture& texture);
	void handleGameState(sf::RenderWindow& window);
	void showPauseMenu(sf::RenderWindow& window);
	void showGameOverMenu(sf::RenderWindow& window);
	void doPauseMenuAction(sf::RenderWindow& window, int chosenItemIdx);
	void doGameOverMenuAction(sf::RenderWindow& window, int chosenItemIdx);
	void resetGame();
	void moveSnake();
	void checkCollision(int nextSnakeHeadPosX, int nextSnakeHeadPosY);
	int getTileSize() const;
	enum GameState { PLAY, PAUSED, GAMEOVER }; // Game states
private:
	enum GameState gameState;
	Menu pauseMenu;
	Menu gameOverMenu;

	// Game background
	sf::RenderTexture texture;
	sf::Sprite background;

	// Game objects
	Apple apple;
	Snake snake;

	// Tile settings
	static constexpr int tileSize = 30;
	static constexpr int mapSizeInTilesX = 29;  // compile-time constant
	static constexpr int mapSizeInTilesY = 29;  // compile-time constant
	Tile tiles[mapSizeInTilesX][mapSizeInTilesY];
	const sf::Color tileColor1;
	const sf::Color tileColor2;
};