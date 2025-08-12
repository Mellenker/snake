#include "includes/Game.hpp"
#include <iostream>

using namespace sf;

Game::Game()
	: snake(initPosX, initPosY),
	apple(),
	colorTile1(Color(0, 132, 9)),
	colorTile2(Color(0, 118, 9))
{
	apple.spawnAtRandomTile(Utils::mapSizeInTilesX - 1, Utils::mapSizeInTilesY - 1);

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

// Handle ingame keyboard input (I don't know about this one...)
void Game::forwardSnakeInput(Keyboard::Key keyPressed) {
	snake.changeDir(keyPressed);
}

// Populate map with tiles
void Game::spawnTiles(RenderTexture& texture) {

	std::cout << "Spawning tiles\n";

	texture.create(Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize);

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

	Vector2i nextHeadPos = getNextSnakeHeadTilePos();
	
	if (detectGameOverCollision(nextHeadPos)) {
		return true;
	}
	
	if (detectAppleCollision(nextHeadPos)) {
		snake.addSegment();
		apple.spawnAtRandomTile(Utils::mapSizeInTilesX - 1, Utils::mapSizeInTilesY - 1);
	}
	
	// Move the snake
	std::cout << "X: " << nextHeadPos.x << "\n";
	snake.move(tiles[nextHeadPos.x][nextHeadPos.y].getPosition());
	snake.setHeadTilePos(nextHeadPos);

	tiles[nextHeadPos.x][nextHeadPos.y].setOccupied(true);

	int tailEndX = snake.getTailEnd().x / Utils::tileSize;
	int tailEndY = snake.getTailEnd().y / Utils::tileSize;

	tiles[tailEndX][tailEndY].setOccupied(false);

	return false;
}

// Good function name or not?
Vector2i Game::getNextSnakeHeadTilePos() {

	Vector2i snakeHeadPos = snake.getHeadTilePos();

	switch (snake.getCurrDir()) {
	case Snake::UP:
		snakeHeadPos.y--;
		break;
	case Snake::LEFT:
		snakeHeadPos.x--;
		break;
	case Snake::DOWN:
		snakeHeadPos.y++;
		break;
	case Snake::RIGHT:
		snakeHeadPos.x++;
		break;
	default:
		break;
	}
	
	return snakeHeadPos;
}

bool Game::detectAppleCollision(Vector2i nextHeadPos) {
	std::cout << "Check Apple Collision \n";
	Vector2i appleTilePos = apple.getAppleTilePos();

	if (nextHeadPos == appleTilePos) {
		return true; // Collision with apple
	}
	else {
		return false;
	}
}

bool Game::detectGameOverCollision(Vector2i nextHeadPos) {
	std::cout << "Check Game Over Colllision \n";

	if (nextHeadPos.y < 0
		|| nextHeadPos.x >= Utils::mapSizeInTilesX
		|| nextHeadPos.y < 0
		|| nextHeadPos.y >= Utils::mapSizeInTilesY)
	{
		return true; // Collision with screen edge
		std::cout << "STAY ON SCREEN" << std::endl;
	}
	else if (tiles[nextHeadPos.x][nextHeadPos.y].isOccupied()
		&& (snake.getCurrDir() != Snake::NONE))
	{
		return true; // Collision with body
		std::cout << "DO NOT COLLIDE WITH BODY" << std::endl;

		std::cout << "AFTER: " << nextHeadPos.x << ", " << nextHeadPos.y<< std::endl;
	}
	else {
		return false; // No collision
	}
}

void Game::resetGame() {
	// Reset snake and apple
	snake = Snake(initPosX, initPosY);
	apple = Apple();
	apple.spawnAtRandomTile(Utils::mapSizeInTilesX - 1, Utils::mapSizeInTilesY - 1);

	// Reset tile occupation
	for (auto& row : tiles) {
		for (auto& elem : row) {
			elem.setOccupied(false);
		}
	}

	snake.setDir(Snake::Direction::NONE);
}
