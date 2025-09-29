#include "../includes/Game.hpp"
#include <iostream>

Game::Game()
	: snake(initSnakeTilePosX, initSnakeTilePosY),
	apple(),
	// Colors should not be hard-coded
	colorTile1(sf::Color(0, 132, 9)),
	colorTile2(sf::Color(0, 118, 9))
{

	// Setup background
	spawnTiles(texture);
	background = sf::Sprite(texture.getTexture());

	// Initialize free tiles
	for (int i = 0; i < (Utils::mapSizeInTilesX * Utils::mapSizeInTilesY); i++) {
		freeTiles.push_back(i);
		posInFreeTiles.push_back(i);
	}

	// Occupy initial snake tiles
	occupyTile(initSnakeTilePosX * Utils::tileSize, initSnakeTilePosY * Utils::tileSize);
	occupyTile((initSnakeTilePosX * Utils::tileSize) - Utils::tileSize, initSnakeTilePosY * Utils::tileSize);

	apple.spawnAtTile(generateRandomFreeTilePos());
}

void Game::drawObjects(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(apple);
	window.draw(snake);
	window.draw(scoreCounter);
	std::cout << "DRAW!\n";
}

void Game::forwardSnakeInput(sf::Keyboard::Key keyPressed) {
	snake.changeDir(keyPressed);
}

// Populate map with tiles
void Game::spawnTiles(sf::RenderTexture& texture) {

	std::cout << "Spawning tiles\n";

	texture.create(Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize);

	int tileNum = 0;

	int xPos = 0;
	int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
	for (int yIt = 0; yIt < Utils::mapSizeInTilesY; yIt++) {
		for (int xIt = 0; xIt < Utils::mapSizeInTilesX; xIt++) {
			Tile tile(Utils::tileSize, xPos, yPos);

			if (colorFlag)
				tile.setColor(colorTile1);
			else
				tile.setColor(colorTile2);
			
			tileNum++;

			xPos += Utils::tileSize;
			texture.draw(tile);
			colorFlag = !colorFlag;
		}
		xPos = 0; // Reset x position after each row
		yPos += Utils::tileSize;
	}
}

bool Game::tryUpdateSnakeState() {

	std::cout << "Try to update snake state\n";

	if (snake.getCurrDir() == Snake::NONE) {
		std::cout << "Snake not moving\n";
		return false; // No movement, no update
	}

	sf::Vector2f nextHeadPos = getNextSnakeHeadPos();
	
	if (detectGameOverCollision(nextHeadPos)) {
		return true;
	}
	
	if (detectAppleCollision(nextHeadPos)) {
		snake.addSegment();
		scoreCounter.addPoint();

		sf::Vector2f nextApplePos = generateRandomFreeTilePos();

		// Make sure apple doesn't spawn in its previous position
		while (detectAppleCollision(nextApplePos)) {
			nextApplePos = generateRandomFreeTilePos();
		}

		apple.spawnAtTile(nextApplePos);

	}
	
	// Move the snake
	std::cout << "X: " << nextHeadPos.x << "\n";
	std::cout << "Y: " << nextHeadPos.y << "\n";

	snake.move(nextHeadPos);

	occupyTile(nextHeadPos.x, nextHeadPos.y);
	freeTile(snake.getTailEnd().x, snake.getTailEnd().y);

	return false;
}

sf::Vector2f Game::getNextSnakeHeadPos() {

	sf::Vector2f snakeHeadPos = snake.getHeadPos();

	switch (snake.getCurrDir()) {
	case Snake::UP:
		snakeHeadPos.y = snakeHeadPos.y - Utils::tileSize;
		break;
	case Snake::LEFT:
		snakeHeadPos.x = snakeHeadPos.x - Utils::tileSize;
		break;
	case Snake::DOWN:
		snakeHeadPos.y = snakeHeadPos.y + Utils::tileSize;
		break;
	case Snake::RIGHT:
		snakeHeadPos.x = snakeHeadPos.x + Utils::tileSize;
		break;
	default:
		break;
	}
	
	return snakeHeadPos;
}

bool Game::detectAppleCollision(sf::Vector2f nextHeadPos) {
	std::cout << "Check Apple Collision \n";
	sf::Vector2f appleTilePos = apple.getApplePos();

	if (nextHeadPos == appleTilePos) {
		return true; // Collision with apple
	}
	else {
		return false;
	}
}

bool Game::detectGameOverCollision(sf::Vector2f nextHeadPos) {
	std::cout << "Check Game Over Colllision \n";

	// Check collision with screen edge
	if (nextHeadPos.x < 0
		|| nextHeadPos.x >= (Utils::mapSizeInTilesX * Utils::tileSize)
		|| nextHeadPos.y < 0
		|| nextHeadPos.y >= (Utils::mapSizeInTilesY * Utils::tileSize))
	{
		std::cout << "STAY ON SCREEN" << std::endl;
		return true; 
	}
	
	int tileId = (nextHeadPos.y / Utils::tileSize) * Utils::mapSizeInTilesX + (nextHeadPos.x / Utils::tileSize);
	int tileIndex = posInFreeTiles[tileId];

	// Check collision with snake body
	if (tileIndex == -1
		&& (snake.getCurrDir() != Snake::NONE))
	{
		std::cout << "DO NOT COLLIDE WITH BODY" << std::endl;
		std::cout << "AFTER: " << nextHeadPos.x << ", " << nextHeadPos.y << std::endl;
		return true;
	}

	return false;
}

void Game::resetGame() {

	snake = Snake(initSnakeTilePosX, initSnakeTilePosY);
	snake.setDir(Snake::Direction::NONE);

	freeTiles.clear();
	posInFreeTiles.clear();
	for (int i = 0; i < (Utils::mapSizeInTilesX * Utils::mapSizeInTilesY); i++) {
		freeTiles.push_back(i);
		posInFreeTiles.push_back(i);
	}

	// Occupy initial snake tiles
	occupyTile(initSnakeTilePosX * Utils::tileSize, initSnakeTilePosY * Utils::tileSize);
	occupyTile((initSnakeTilePosX * Utils::tileSize) - Utils::tileSize, initSnakeTilePosY * Utils::tileSize);

	apple = Apple();
	sf::Vector2f nextApplePos = generateRandomFreeTilePos();
	
	// Make sure apple doesn't spawn in its previous position
	while (detectAppleCollision(nextApplePos)) {
		nextApplePos = generateRandomFreeTilePos();
	}

	apple.spawnAtTile(nextApplePos);
	scoreCounter.resetPoints();
}

int getTileID(int x, int y) {
	return (y / Utils::tileSize) * Utils::mapSizeInTilesX + (x / Utils::tileSize);
}

void Game::occupyTile(int x, int y) {

	int tileId = getTileID(x, y);
	int tilePos = posInFreeTiles[tileId];

	// If this is 0, the tile is already occupied
	if (tilePos != -1) {
		int lastFreeTileId = freeTiles.back();
		freeTiles[tilePos] = lastFreeTileId;
		posInFreeTiles[lastFreeTileId] = tilePos;
		freeTiles.pop_back();
		posInFreeTiles[tileId] = -1;
	}
	else {
		std::cout << "Tile already occupied!\n";
	}
}

void Game::freeTile(int x, int y) {
	
	int tileId = getTileID(x, y);
	int tilePos = posInFreeTiles[tileId];

	if (tilePos == -1) {
		freeTiles.push_back(tileId);
		posInFreeTiles[tileId] = freeTiles.size() - 1;
	}
	else {
		std::cout << "Tile already free!\n";
	}
}

sf::Vector2f Game::generateRandomFreeTilePos() {
	// Generate random coordinates
	std::random_device random;
	std::mt19937 rng(random());

	int min = 0;
	int max = freeTiles.size() - 1;

	std::uniform_int_distribution<> disY(min, max);
	int randomFreeTileIdx = disY(rng);
	
	// Translate freeTile ID to coordinates
	int x = freeTiles[randomFreeTileIdx] % Utils::mapSizeInTilesX;
	int y = freeTiles[randomFreeTileIdx] / Utils::mapSizeInTilesX;

	return sf::Vector2f(x * Utils::tileSize, y * Utils::tileSize);

}
