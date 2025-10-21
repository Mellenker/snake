#include "Game.hpp"

Game::Game()
	: initSnakeTilePosX(2),
	initSnakeTilePosY(2),
	snake(initSnakeTilePosX, initSnakeTilePosY),
	texture(sf::Vector2u(Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize)),
	background(texture.getTexture()) // Texture empty at this point
{
	// Setup background
	spawnTiles(texture);
	background.setTexture(texture.getTexture(), true);
	initializeFreeTiles();

	// Occupy initial snake tiles
	occupyTile(initSnakeTilePosX * Utils::tileSize, initSnakeTilePosY * Utils::tileSize);
	occupyTile((initSnakeTilePosX * Utils::tileSize) - Utils::tileSize, initSnakeTilePosY * Utils::tileSize);

	apple.spawnAtTile(generateRandomFreeTilePos());
}

void Game::initializeFreeTiles() {

	for (int i = 0; i < (Utils::mapSizeInTilesX * Utils::mapSizeInTilesY); i++) {
		freeTiles.push_back(i);
		posInFreeTiles.push_back(i);
	}
}

void Game::drawObjects(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(apple);
	window.draw(snake);
	window.draw(scoreCounter);
}

void Game::forwardSnakeInput(sf::Keyboard::Key keyPressed) {
	snake.changeDir(keyPressed);
}

// Populate map with tiles
void Game::spawnTiles(sf::RenderTexture& texture) {

	int tileNum = 0;

	int xPos = 0;
	int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
	for (int yIt = 0; yIt < Utils::mapSizeInTilesY; yIt++) {
		for (int xIt = 0; xIt < Utils::mapSizeInTilesX; xIt++) {
			sf::RectangleShape tile(sf::Vector2f(Utils::tileSize, Utils::tileSize));
			
			tile.setPosition(sf::Vector2f(xPos, yPos));

			if (colorFlag)
				tile.setFillColor(Colors::grassDark);
			else
				tile.setFillColor(Colors::grassLight);
			
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

	if (snake.getCurrDir() == Snake::NONE) {
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
	sf::Vector2f appleTilePos = apple.getApplePos();

	if (nextHeadPos == appleTilePos) {
		return true;
	}
	else {
		return false;
	}
}

int getTileID(int x, int y) {
	return (((y / Utils::tileSize) * Utils::mapSizeInTilesX) + (x / Utils::tileSize));
}

bool Game::detectGameOverCollision(sf::Vector2f nextHeadPos) {

	// Check collision with screen edge
	if (nextHeadPos.x < 0
		|| nextHeadPos.x >= (Utils::mapSizeInTilesX * Utils::tileSize)
		|| nextHeadPos.y < 0
		|| nextHeadPos.y >= (Utils::mapSizeInTilesY * Utils::tileSize))
	{
		return true; 
	}
	
	int tileId = getTileID(nextHeadPos.x, nextHeadPos.y);
	int tileIndex = posInFreeTiles[tileId];

	// Check collision with snake body
	if (tileIndex == -1
		&& (snake.getCurrDir() != Snake::NONE))
	{
		return true;
	}

	return false;
}

void Game::resetGame() {

	snake = Snake(initSnakeTilePosX, initSnakeTilePosY);
	snake.setDir(Snake::Direction::NONE);

	freeTiles.clear();
	posInFreeTiles.clear();
	initializeFreeTiles();

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
}

void Game::freeTile(int x, int y) {
	
	int tileId = getTileID(x, y);
	int tilePos = posInFreeTiles[tileId];

	if (tilePos == -1) {
		freeTiles.push_back(tileId);
		posInFreeTiles[tileId] = freeTiles.size() - 1;
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
