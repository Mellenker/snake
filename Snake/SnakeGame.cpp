#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <mutex>

#include "includes/Snake.h"
#include "includes/Tile.h"
#include "includes/Apple.h"
#include "includes/Menu.h"

using namespace sf;

// Framerate limit
const int fpsLimit = 3;

// Window settings
const int winSizeInTilesX = 29;
const int winSizeInTilesY = 29;

// Tile settings
Tile tiles[winSizeInTilesX][winSizeInTilesY];
int tileSize = 30;
Color tileColor1 = Color(0, 132, 9);
Color tileColor2 = Color(0, 118, 9);

// Snake settings
int snakeStartX = 4;
int snakeStartY = 4;
Color colorSnakeHead = Color(103, 0, 255);
Color colorSnakeTail = Color(143, 0, 204);

// Game states
enum GameState { PLAY, PAUSE, GAMEOVER };
enum GameState gameState;

// Snake directions
enum Direction { UP, LEFT, RIGHT, DOWN, STILL };
enum Direction direction;

// Populate map with tiles
void spawnTiles(RenderTexture& texture) {
	texture.create(winSizeInTilesX * tileSize, winSizeInTilesY * tileSize);
	
	int xPos = 0;
	int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
	for (int yIt = 0; yIt < winSizeInTilesY; yIt++) {
		for (int xIt = 0; xIt < winSizeInTilesX; xIt++) {
			Tile tile(tileSize, xPos, yPos);

			if (colorFlag)
				tile.setColor(tileColor1);
			else
				tile.setColor(tileColor2);

			tiles[xIt][yIt] = tile;
			xPos += tileSize;
			tile.draw(texture);
			colorFlag = !colorFlag;
		}
		xPos = 0; // Reset x position after each row
		yPos += tileSize;
	}
}

// Handle keyboard input
void handleKeyboardInput(Keyboard::Key keyPressed) {
	switch (keyPressed) {
	case Keyboard::Key::Escape:
		gameState = PAUSE;
		break;
	case Keyboard::Key::W:
		if (direction != DOWN)
			direction = UP;
		break;
	case Keyboard::Key::A:
		if (direction != RIGHT)
			direction = LEFT;
		break;
	case Keyboard::Key::S:
		if (direction != UP)
			direction = DOWN;
		break;
	case Keyboard::Key::D:
		if (direction != LEFT)
			direction = RIGHT;
		break;
	default:
		break;
	}
	return;
}

int main() {
	RenderWindow window(VideoMode(winSizeInTilesX * tileSize, winSizeInTilesY * tileSize), "SnakeGame");

	// Prepare menus
	Menu gameOverMenu(window.getSize().x, window.getSize().y);
	gameOverMenu.setTitle("Game Over");
	gameOverMenu.addItem("Restart");
	gameOverMenu.addItem("Exit");
	
	// Create background with tiles
	RenderTexture texture;
	spawnTiles(texture);
	Sprite background(texture.getTexture());

	// Initiate game objects
	Snake snake(snakeStartX, snakeStartY, tileSize, colorSnakeHead, colorSnakeTail);
	Apple apple(tileSize);
	apple.placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);

	gameState = PLAY;
	direction = STILL;

	window.setFramerateLimit(fpsLimit);

	// GAME LOOP
	while (window.isOpen() && gameState == PLAY) {

		// Current snake position
		int xSnakeHead = snake.getHeadTileCoords()['x'];
		int ySnakeHead = snake.getHeadTileCoords()['y'];

		// Current apple position
		int xApple = apple.getAppleCoords()['x'];
		int yApple = apple.getAppleCoords()['y'];

		Event event;

		// Handle events
		bool firstLoopThisFrame = true; // Can this be removed?
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// Keyboard input
			if (event.type == Event::KeyPressed && firstLoopThisFrame) {
				handleKeyboardInput(event.key.code);
				firstLoopThisFrame = false;
			}
		}

		// Movement
		switch (direction) {
		case UP:
			ySnakeHead--;
			break;
		case LEFT:
			xSnakeHead--;
			break;
		case DOWN:
			ySnakeHead++;
			break;
		case RIGHT:
			xSnakeHead++;
			break;
		default:
			break;
		}


		// Collision checks
		if (xSnakeHead == xApple && ySnakeHead == yApple) {
			// Add score here
			snake.addSegment();
			apple.placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);
		}

		if ((xSnakeHead < 0 || xSnakeHead >= winSizeInTilesX) || (ySnakeHead < 0 || ySnakeHead >= winSizeInTilesY)) {
			gameState = GAMEOVER;
			std::cout << "STAY ON SCREEN" << std::endl;
		}
		else if (tiles[xSnakeHead][ySnakeHead].isOccupied() && (direction != STILL)) {
			gameState = GAMEOVER;
			std::cout << "DO NOT COLLIDE WITH TAIL" << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(120000));

		}
		else {
			// Move the snake
			snake.move(tiles[xSnakeHead][ySnakeHead].getPosition());
			snake.setHeadTileCoords(xSnakeHead, ySnakeHead);

			// Set tile occupation
			tiles[xSnakeHead][ySnakeHead].setOccupied(true);

			int xTailEnd = snake.getTailEnd().x / tileSize;
			int yTailEnd = snake.getTailEnd().y / tileSize;

			tiles[xTailEnd][yTailEnd].setOccupied(false);

		}

		window.clear();

		// Draw game objects
		window.draw(background);
		snake.draw(window);
		apple.draw(window);

		// Handle game state
		switch (gameState) {
		case PAUSE:
			std::cout << "PAUSE" << std::endl;
			gameState = PLAY;
			break;
		case GAMEOVER:
			std::cout << "GAMEOVER" << std::endl;
			gameOverMenu.updateTexture();
			gameOverMenu.drawToWindow(window);
			// Handle stopping of game
			break;
		}

		window.display();
	}
	// GAMEOVER LOOP (REMOVE BUSY WAITING!)
	while (window.isOpen() && gameState == GAMEOVER) {
		
		Event event;
		
		// Handle events
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case Keyboard::Key::W:
					gameOverMenu.moveUp();
					break;
				case Keyboard::Key::S:
					gameOverMenu.moveDown();
					break;
				case Keyboard::Key::Enter:
					// Perform button event
					break;
				default:
					break;
				}
			}

		}

		// Draw changes
		window.clear();
		gameOverMenu.updateTexture();
		gameOverMenu.drawToWindow(window);
		window.display();
	}

	return 0;
}

