#include "includes/Game.h"
#include <iostream>

using namespace sf;

/*
What should be handled:
- Game states: PLAY, PAUSED, GAMEOVER
- PAUSE MENU, GAMEOVER MENU
*/

Game::Game()
	: snake(tileSize, 1, 1, Color(103, 0, 255), Color(143, 0, 204)), 
	apple(tileSize), 
	tileColor1(Color(0, 132, 9)), 
	tileColor2(Color(0, 118, 9))
{

	initGame();

	// Setup background
	spawnTiles(texture);
	background = Sprite(texture.getTexture());
}

void Game::drawGameObjects(RenderWindow& window) {
	window.draw(background);
	window.draw(apple);
	window.draw(snake);

	std::cout << "DRAW!\n";
}

// Handle ingame keyboard input
void Game::handleKeyboardInput(Keyboard::Key keyPressed) {
	if (keyPressed == Keyboard::Key::Escape) {
		gameState = PAUSED;
		std::cout << "PAUSE\n";
	}
	else if (gameState == PLAY) {
		snake.handleInput(keyPressed);
	}
}

// Populate map with tiles
void Game::spawnTiles(RenderTexture& texture) {

	std::cout << "Spawning tiles\n";

	texture.create(mapSizeInTilesX * tileSize, mapSizeInTilesY * tileSize);

	int xPos = 0;
	int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
	for (int yIt = 0; yIt < mapSizeInTilesY; yIt++) {
		for (int xIt = 0; xIt < mapSizeInTilesX; xIt++) {
			Tile tile(tileSize, xPos, yPos);

			if (colorFlag)
				tile.setColor(tileColor1);
			else
				tile.setColor(tileColor2);

			tiles[xIt][yIt] = tile;
			xPos += tileSize;
			texture.draw(tile);
			colorFlag = !colorFlag;
		}
		xPos = 0; // Reset x position after each row
		yPos += tileSize;
	}
}

std::map<char, int> Game::getMapSizeInTiles() const {
	std::map<char, int> mapSize = {
		{'x', mapSizeInTilesX},
		{'y', mapSizeInTilesY}
	};
	return mapSize;
}

void Game::initGame() {
	apple.placeAppleRandomly(tileSize, mapSizeInTilesX - 1, mapSizeInTilesY - 1);

	gameState = PLAY;
	snake.setDir(Snake::Direction::STILL); // Set initial direction to STILL
}

void Game::moveSnake() {

	std::map<char, int> snakeCoords = snake.getHeadTileCoords();

	switch (snake.getCurrDir()) {
	case Snake::UP:
		snakeCoords['y']--;
		break;
	case Snake::LEFT:
		snakeCoords['x']--;
		break;
	case Snake::DOWN:
		snakeCoords['y']++;
		break;
	case Snake::RIGHT:
		snakeCoords['x']++;
		break;
	default:
		break;
	}

	checkCollision(snakeCoords['x'], snakeCoords['y']);
}

int Game::getTileSize() const {
	return tileSize;
}

void Game::checkCollision(int nextHeadX, int nextHeadY) {
	std::cout << "Check Colllision \n";

	std::map<char, int> appleCoords = apple.getAppleCoords();

	// Apple
	if (nextHeadX == appleCoords['x']
		&& nextHeadY == appleCoords['y']) {
		// Add score here
		snake.addSegment();
		apple.placeAppleRandomly(tileSize, mapSizeInTilesX - 1, mapSizeInTilesY - 1);
	}

	// Wall and tail (Game Over checks)
	if (nextHeadX < 0
		|| nextHeadX >= mapSizeInTilesX
		|| nextHeadY < 0
		|| nextHeadY >= mapSizeInTilesY)
	{
			gameState = GAMEOVER;
			std::cout << "STAY ON SCREEN" << std::endl;
	}
	else if (tiles[nextHeadX][nextHeadY].isOccupied()
		&& (snake.getCurrDir() != Snake::STILL))
	{
		gameState = GAMEOVER;
		std::cout << "DO NOT COLLIDE WITH TAIL" << std::endl;

		std::cout << "AFTER: " << nextHeadX << ", " << nextHeadY << std::endl;
	}
	// If no collision, move the snake
	else {
		snake.move(tiles[nextHeadX][nextHeadY].getPosition());
		snake.setHeadTileCoords(nextHeadX, nextHeadY);

		tiles[nextHeadX][nextHeadY].setOccupied(true);

		int xTailEnd = snake.getTailEnd().x / tileSize;
		int yTailEnd = snake.getTailEnd().y / tileSize;

		tiles[xTailEnd][yTailEnd].setOccupied(false);

	}
}





