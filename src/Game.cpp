#include "Game.hpp"

Game::Game() : 
	m_initSnakeTilePosX(2),
	m_initSnakeTilePosY(2),
	m_snake(m_initSnakeTilePosX, m_initSnakeTilePosY),
	m_texture(sf::Vector2u(Utils::g_mapSizeInTilesX * Utils::g_tileSize, Utils::g_mapSizeInTilesY * Utils::g_tileSize)),
	m_background(m_texture.getTexture()) // Texture empty at this point
{
	// Setup background
	spawnTiles(m_texture);
	m_background.setTexture(m_texture.getTexture(), true);
	initializeFreeTiles();

	// Occupy initial snake tiles
	occupyTile(m_initSnakeTilePosX * Utils::g_tileSize, m_initSnakeTilePosY * Utils::g_tileSize);
	occupyTile((m_initSnakeTilePosX * Utils::g_tileSize) - Utils::g_tileSize, m_initSnakeTilePosY * Utils::g_tileSize);

	m_apple.spawnAtTile(generateRandomFreeTilePos());
}

void Game::initializeFreeTiles() {

	for (int i = 0; i < (Utils::g_mapSizeInTilesX * Utils::g_mapSizeInTilesY); i++) {
		m_freeTiles.push_back(i);
		m_posInFreeTiles.push_back(i);
	}
}

void Game::drawObjects(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_apple);
	window.draw(m_snake);
	window.draw(m_scoreCounter);
}

void Game::forwardSnakeInput(sf::Keyboard::Key keyPressed) {
	m_snake.changeDir(keyPressed);
}

// Populate map with tiles
void Game::spawnTiles(sf::RenderTexture& texture) {

	int tileNum = 0;

	int xPos = 0;
	int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
	for (int yIt = 0; yIt < Utils::g_mapSizeInTilesY; yIt++) {
		for (int xIt = 0; xIt < Utils::g_mapSizeInTilesX; xIt++) {
			sf::RectangleShape tile(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize));
			
			tile.setPosition(sf::Vector2f(xPos, yPos));

			if (colorFlag)
				tile.setFillColor(Colors::grassDark);
			else
				tile.setFillColor(Colors::grassLight);
			
			tileNum++;

			xPos += Utils::g_tileSize;
			texture.draw(tile);
			colorFlag = !colorFlag;
		}
		xPos = 0; // Reset x position after each row
		yPos += Utils::g_tileSize;
	}
}

bool Game::tryUpdateSnakeState() {

	if (m_snake.getCurrDir() == Snake::NONE) {
		return false; // No movement, no update
	}

	sf::Vector2f nextHeadPos = getNextSnakeHeadPos();
	
	if (detectGameOverCollision(nextHeadPos)) {
		return true;
	}
	
	if (detectAppleCollision(nextHeadPos)) {
		m_snake.addSegment();
		m_scoreCounter.addPoint();

		sf::Vector2f nextApplePos = generateRandomFreeTilePos();

		// Make sure apple doesn't spawn in its previous position
		while (detectAppleCollision(nextApplePos)) {
			nextApplePos = generateRandomFreeTilePos();
		}

		m_apple.spawnAtTile(nextApplePos);

	}
	
	m_snake.move(nextHeadPos);

	occupyTile(nextHeadPos.x, nextHeadPos.y);
	freeTile(m_snake.getTailEnd().x, m_snake.getTailEnd().y);

	return false;
}

sf::Vector2f Game::getNextSnakeHeadPos() {

	sf::Vector2f snakeHeadPos = m_snake.getHeadPos();

	switch (m_snake.getCurrDir()) {
	case Snake::UP:
		snakeHeadPos.y = snakeHeadPos.y - Utils::g_tileSize;
		break;
	case Snake::LEFT:
		snakeHeadPos.x = snakeHeadPos.x - Utils::g_tileSize;
		break;
	case Snake::DOWN:
		snakeHeadPos.y = snakeHeadPos.y + Utils::g_tileSize;
		break;
	case Snake::RIGHT:
		snakeHeadPos.x = snakeHeadPos.x + Utils::g_tileSize;
		break;
	default:
		break;
	}
	
	return snakeHeadPos;
}

bool Game::detectAppleCollision(sf::Vector2f nextHeadPos) {
	sf::Vector2f appleTilePos = m_apple.getApplePos();

	if (nextHeadPos == appleTilePos) {
		return true;
	}
	else {
		return false;
	}
}

int getTileID(int x, int y) {
	return (((y / Utils::g_tileSize) * Utils::g_mapSizeInTilesX) + (x / Utils::g_tileSize));
}

bool Game::detectGameOverCollision(sf::Vector2f nextHeadPos) {

	// Check collision with screen edge
	if (nextHeadPos.x < 0
		|| nextHeadPos.x >= (Utils::g_mapSizeInTilesX * Utils::g_tileSize)
		|| nextHeadPos.y < 0
		|| nextHeadPos.y >= (Utils::g_mapSizeInTilesY * Utils::g_tileSize))
	{
		return true; 
	}
	
	int tileId = getTileID(nextHeadPos.x, nextHeadPos.y);
	int tileIndex = m_posInFreeTiles[tileId];

	// Check collision with snake body
	if (tileIndex == -1
		&& (m_snake.getCurrDir() != Snake::NONE))
	{
		return true;
	}

	return false;
}

void Game::resetGame() {

	m_snake = Snake(m_initSnakeTilePosX, m_initSnakeTilePosY);
	m_snake.setDir(Snake::Direction::NONE);

	m_freeTiles.clear();
	m_posInFreeTiles.clear();
	initializeFreeTiles();

	// Occupy initial snake tiles
	occupyTile(m_initSnakeTilePosX * Utils::g_tileSize, m_initSnakeTilePosY * Utils::g_tileSize);
	occupyTile((m_initSnakeTilePosX * Utils::g_tileSize) - Utils::g_tileSize, m_initSnakeTilePosY * Utils::g_tileSize);

	m_apple = Apple();
	sf::Vector2f nextApplePos = generateRandomFreeTilePos();
	
	// Make sure apple doesn't spawn in its previous position
	while (detectAppleCollision(nextApplePos)) {
		nextApplePos = generateRandomFreeTilePos();
	}

	m_apple.spawnAtTile(nextApplePos);
	m_scoreCounter.resetPoints();
}

void Game::occupyTile(int x, int y) {

	int tileId = getTileID(x, y);
	int tilePos = m_posInFreeTiles[tileId];

	// If this is 0, the tile is already occupied
	if (tilePos != -1) {
		int lastFreeTileId = m_freeTiles.back();
		m_freeTiles[tilePos] = lastFreeTileId;
		m_posInFreeTiles[lastFreeTileId] = tilePos;
		m_freeTiles.pop_back();
		m_posInFreeTiles[tileId] = -1;
	}
}

void Game::freeTile(int x, int y) {
	
	int tileId = getTileID(x, y);
	int tilePos = m_posInFreeTiles[tileId];

	if (tilePos == -1) {
		m_freeTiles.push_back(tileId);
		m_posInFreeTiles[tileId] = m_freeTiles.size() - 1;
	}
}

sf::Vector2f Game::generateRandomFreeTilePos() {
	
	// Generate random coordinates
	std::random_device random;
	std::mt19937 rng(random());

	int min = 0;
	int max = m_freeTiles.size() - 1;

	std::uniform_int_distribution<> disY(min, max);
	int randomFreeTileIdx = disY(rng);
	
	// Translate freeTile ID to coordinates
	int x = m_freeTiles[randomFreeTileIdx] % Utils::g_mapSizeInTilesX;
	int y = m_freeTiles[randomFreeTileIdx] / Utils::g_mapSizeInTilesX;

	return sf::Vector2f(x * Utils::g_tileSize, y * Utils::g_tileSize);

}
