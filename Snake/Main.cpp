#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <mutex>
#include <memory>

#include "includes/Snake.h"
#include "includes/Tile.h"
#include "includes/Apple.h"
#include "includes/GameOverMenu.h"
#include "includes/PauseMenu.h"

using namespace sf;

// Framerate limit (may not be needed)
const int inGameFPSLimit = 10;
const int menuFPSLimit = 30;

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
enum GameState { PLAY, PAUSED, GAMEOVER };
enum GameState gameState;

// Snake directions
enum Direction { UP, LEFT, RIGHT, DOWN, STILL };
enum Direction currDir;

// Smart pointers
std::unique_ptr<RenderWindow> window;
std::unique_ptr<GameOverMenu> gameOverMenu;
std::unique_ptr<PauseMenu> pauseMenu;
std::unique_ptr<Sprite> background;
std::unique_ptr<Snake> snake;
std::unique_ptr<Apple> apple;

// Function declarations
void spawnTiles(RenderTexture& texture);
void handleKeyboardInput(Keyboard::Key keyPressed);
void showPauseMenu();
void doPauseMenuAction(int chosenItemIdx);
void showGameOverMenu();
void doGameOverMenuAction(int chosenItemIdx);
void enterGame();
void initGame();
void resetGame();

// Main function
int main() {

	window = std::make_unique<RenderWindow>(VideoMode(winSizeInTilesX * tileSize, winSizeInTilesY * tileSize), "SnakeGame");

	// Prepare menus (Make unique constructors for menu types!)
	gameOverMenu = std::make_unique<GameOverMenu>(window->getSize().x, window->getSize().y);
	pauseMenu = std::make_unique<PauseMenu>(window->getSize().x, window->getSize().y);

	// Create background with tiles
	RenderTexture texture;
	spawnTiles(texture);
	background = std::make_unique<Sprite>(texture.getTexture());

	// Set initial game state
	initGame();

	enterGame();

	return 0;
}

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

// Handle ingame keyboard input
void handleKeyboardInput(Keyboard::Key keyPressed) {
	switch (keyPressed) {
	case Keyboard::Key::Escape:
		gameState = PAUSED;
		break;
	case Keyboard::Key::W:
		if (currDir != DOWN)
			std::cout << "UP" << std::endl;
		currDir = UP;
		break;
	case Keyboard::Key::A:
		if (currDir != RIGHT)
			std::cout << "LEFT" << std::endl;
		currDir = LEFT;
		break;
	case Keyboard::Key::S:
		if (currDir != UP)
			std::cout << "DOWN" << std::endl;
		currDir = DOWN;
		break;
	case Keyboard::Key::D:
		if (currDir != LEFT)
			std::cout << "RIGHT" << std::endl;
		currDir = RIGHT;
		break;
	default:
		break;
	}
	return;
}

void enterGame() {

	// GAME LOOP
	while (window->isOpen() && gameState == PLAY) {

		// Current snake position
		int xSnakeHead = snake->getHeadTileCoords()['x'];
		int ySnakeHead = snake->getHeadTileCoords()['y'];

		// Current apple position
		int xApple = apple->getAppleCoords()['x'];
		int yApple = apple->getAppleCoords()['y'];

		Event event;

		// Handle events
		bool firstLoopThisFrame = true; // Can this be removed?
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();

			// Keyboard input
			if (event.type == Event::KeyPressed) {
				std::cout << "Key pressed" << std::endl;
				handleKeyboardInput(event.key.code);
				firstLoopThisFrame = false;
			}

		}

		// Movement
		switch (currDir) {
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
			snake->addSegment();
			apple->placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);
		}

		if ((xSnakeHead < 0 || xSnakeHead >= winSizeInTilesX) || (ySnakeHead < 0 || ySnakeHead >= winSizeInTilesY)) {
			gameState = GAMEOVER;
			std::cout << "STAY ON SCREEN" << std::endl;
		}
		else if (tiles[xSnakeHead][ySnakeHead].isOccupied() && (currDir != STILL)) {
			gameState = GAMEOVER;
			std::cout << "DO NOT COLLIDE WITH TAIL" << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(120000));

		}
		else {
			// Move the snake
			snake->move(tiles[xSnakeHead][ySnakeHead].getPosition());
			snake->setHeadTileCoords(xSnakeHead, ySnakeHead);

			// Set tile occupation
			tiles[xSnakeHead][ySnakeHead].setOccupied(true);

			int xTailEnd = snake->getTailEnd().x / tileSize;
			int yTailEnd = snake->getTailEnd().y / tileSize;

			tiles[xTailEnd][yTailEnd].setOccupied(false);

		}

		window->clear();

		// Draw game objects
		window->draw(*background);
		snake->draw(*window);
		apple->draw(*window);

		// Handle game state
		switch (gameState) {
		case PAUSED:
			std::cout << "PAUSE" << std::endl;
			showPauseMenu();
			break;
		case GAMEOVER:
			std::cout << "GAMEOVER" << std::endl;
			showGameOverMenu();
			break;
		}

		window->display();
	}
}

void showPauseMenu() {

	window->setFramerateLimit(menuFPSLimit);
	pauseMenu->draw(*window);
	window->display();

	// PAUSE MENU LOOP
	while (window->isOpen() && gameState == PAUSED) {
		Event event;
		Event lastKeyPressedEvent;

		// Block until at least one event is available
		if (window->waitEvent(event)) {
			lastKeyPressedEvent = event;
			
			if (event.type == Event::Closed) {
				window->close();
			}
			if (event.type == Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}
			
			// Drain the rest of the queue, keeping only the last KeyPressed event
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed) {
					window->close();
					break;
				}
				if (event.type == Event::KeyPressed) {
					lastKeyPressedEvent = event;
				}
			}
 
			// Process only the latest event
			if (lastKeyPressedEvent.type == Event::KeyPressed) {
				switch (lastKeyPressedEvent.key.code) {
				case Keyboard::Key::W:
					pauseMenu->moveUp();
					break;
				case Keyboard::Key::S:
					pauseMenu->moveDown();
					break;
				case Keyboard::Key::Enter:
					doPauseMenuAction(pauseMenu->getHighlightedIdx());
					break;
				case Keyboard::Key::Escape:
					window->setFramerateLimit(inGameFPSLimit);
					gameState = PLAY;
					break;
				default:
					break;
				}
			}

			std::cout << "FRAME" << std::endl;

			// Clear window
			window->clear();

			// Draw background game
			window->draw(*background);
			snake->draw(*window);
			apple->draw(*window);

			// Draw changes
			pauseMenu->draw(*window);
			window->display();

		}
	}
}

void showGameOverMenu() {

	window->setFramerateLimit(menuFPSLimit);
	gameOverMenu->draw(*window);
	window->display();

	// PAUSE MENU LOOP
	while (window->isOpen() && gameState == GAMEOVER) {
		Event event;
		Event lastKeyPressedEvent;

		// Block until at least one event is available
		if (window->waitEvent(event)) {
			lastKeyPressedEvent = event;

			if (event.type == Event::Closed) {
				window->close();
			}
			if (event.type == Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}

			// Drain the rest of the queue, keeping only the last KeyPressed event
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed) {
					window->close();
					break;
				}
				if (event.type == Event::KeyPressed) {
					lastKeyPressedEvent = event;
				}
			}

			// Process only the latest event
			if (lastKeyPressedEvent.type == Event::KeyPressed) {
				switch (lastKeyPressedEvent.key.code) {
				case Keyboard::Key::W:
					gameOverMenu->moveUp();
					break;
				case Keyboard::Key::S:
					gameOverMenu->moveDown();
					break;
				case Keyboard::Key::Enter:
					doGameOverMenuAction(gameOverMenu->getHighlightedIdx());
					break;
				case Keyboard::Key::Escape:
					window->setFramerateLimit(inGameFPSLimit);
					gameState = PLAY;
					break;
				default:
					break;
				}
			}

			std::cout << "FRAME" << std::endl;

			// Clear window
			window->clear();

			// Draw background game
			window->draw(*background);
			snake->draw(*window);
			apple->draw(*window);

			// Draw changes
			gameOverMenu->draw(*window);
			window->display();

		}
	}
}

void doPauseMenuAction(int chosenItemIdx) {
	switch (chosenItemIdx) {
	case 0:
		window->setFramerateLimit(inGameFPSLimit);
		gameState = PLAY;
		break;
	case 1:
		resetGame();
		initGame();
		break;
	case 2:
		window->close();
		break;
	default:
		break;
	}
}

void doGameOverMenuAction(int chosenItemIdx) {
	switch (chosenItemIdx) {
	case 0:
		resetGame();
		initGame();
		break;
	case 1:
		window->close();
		break;
	default:
		break;
	}
}

void resetGame() {
	snake.reset();
	apple.reset();

	// Reset tile occupation
	for (auto& row : tiles) {
		for (auto& elem : row) {
			elem.setOccupied(false);
		}
	}
}

void initGame() {
	snake = std::make_unique<Snake>(tileSize, snakeStartX, snakeStartY, colorSnakeHead, colorSnakeTail);
	apple = std::make_unique<Apple>(tileSize);
	apple->placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);

	window->setFramerateLimit(inGameFPSLimit);

	gameState = PLAY;
	currDir = STILL;
}



