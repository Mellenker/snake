#include "../includes/Game.hpp"
#include <iostream>

Game::Game()
	: snake(initSnakeTilePosX, initSnakeTilePosY),
	apple(),
	colorTile1(sf::Color(0, 132, 9)),
	colorTile2(sf::Color(0, 118, 9))
{
	int maxTileId = (Utils::mapSizeInTilesX * Utils::mapSizeInTilesY) - 1;

	// Setup background
	spawnTiles(texture);
	background = sf::Sprite(texture.getTexture());

	// Set scale of game objects
	background.setScale(Utils::scale, Utils::scale);

	apple.spawnAtTile(generateRandomFreeTilePos());
}

void Game::drawGameObjects(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(apple);
	window.draw(snake);
	std::cout << "DRAW!\n";
}

// Handle ingame keyboard input (I don't know about this one...)
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

			tiles[xIt][yIt] = tile;
			
			freeTiles.push_back(tileNum);
			posInFreeTiles.push_back(tileNum);
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

	std::cout << "Try Update Snake State\n";

	sf::Vector2f nextHeadPos = getNextSnakeHeadTilePos();
	
	if (detectGameOverCollision(nextHeadPos)) {
		return true;
	}
	
	if (detectAppleCollision(nextHeadPos)) {
		apple.spawnAtTile(generateRandomFreeTilePos());
	}
	
	// Move the snake

	std::cout << "X: " << nextHeadPos.x << "\n";
	std::cout << "Y: " << nextHeadPos.y << "\n";

	snake.move(nextHeadPos);

	occupyTile(nextHeadPos.x, nextHeadPos.y);

	int tailEndX = snake.getTailEnd().x / Utils::tileSize;
	int tailEndY = snake.getTailEnd().y / Utils::tileSize;

	freeTile(tailEndX, tailEndY);

	return false;
}

// Good function name or not?
sf::Vector2f Game::getNextSnakeHeadTilePos() {

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

	if (nextHeadPos.x < 0
		|| nextHeadPos.x >= Utils::mapSizeInTilesX
		|| nextHeadPos.y < 0
		|| nextHeadPos.y >= Utils::mapSizeInTilesY)
	{
		std::cout << "STAY ON SCREEN" << std::endl;
		return true; // Collision with screen edge
	}
	
	int tileId = nextHeadPos.y * Utils::mapSizeInTilesX + nextHeadPos.x;
	int tileIndex = posInFreeTiles[tileId];

	if (tileIndex == -1
		&& (snake.getCurrDir() != Snake::NONE))
	{
		std::cout << "DO NOT COLLIDE WITH BODY" << std::endl;
		std::cout << "AFTER: " << nextHeadPos.x << ", " << nextHeadPos.y << std::endl;
		return true; // Collision with body
	}

	return false; // No collision
}

void Game::resetGame() {
	// Reset snake and apple
	snake = Snake(initSnakeTilePosX * Utils::tileSize, initSnakeTilePosY * Utils::tileSize);
	apple = Apple();

	apple.spawnAtTile(generateRandomFreeTilePos());

	// Reset tile occupation
	for (auto& row : tiles) {
		for (auto& elem : row) {
			elem.setOccupied(false);
		}
	}

	snake.setDir(Snake::Direction::NONE);
}

void Game::occupyTile(int x, int y) {

	int tileId = y * Utils::mapSizeInTilesX + x;
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
	
	int tileId = y * Utils::mapSizeInTilesX + x;
	int tilePos = posInFreeTiles[tileId];

	if (tilePos == -1) {
		freeTiles.push_back(tileId);
		posInFreeTiles[tileId] = freeTiles.size() - 1;
	}
	else {
		std::cout << "Tile already free!\n";
	}
}

sf::Vector2i Game::generateRandomFreeTilePos() {
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

	return sf::Vector2i(x * Utils::tileSize, y * Utils::tileSize);

}
