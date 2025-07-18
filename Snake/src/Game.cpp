#include "includes/Game.h"
#include <iostream>

using namespace sf;

/*
What should be handled:
- Game states: PLAY, PAUSED, GAMEOVER
- PAUSE MENU, GAMEOVER MENU
*/

Game::Game()
	: snake(tileSize, 1, 1, Color(103, 0, 255), Color(143, 0, 204)), // Fix magic numbers!
	apple(tileSize),
	tileColor1(Color(0, 132, 9)),
	tileColor2(Color(0, 118, 9)),

	pauseMenu(mapSizeInTilesX* tileSize, mapSizeInTilesY* tileSize),
	gameOverMenu(mapSizeInTilesX* tileSize, mapSizeInTilesY* tileSize)
{

	// Prepare menus 
	pauseMenu.setTitle("Paused");
	pauseMenu.addItem("Unpause");
	pauseMenu.addItem("Restart");
	pauseMenu.addItem("Exit");

	gameOverMenu.setTitle("Game Over");
	gameOverMenu.addItem("Restart");
	gameOverMenu.addItem("Exit");

	apple.placeAppleRandomly(tileSize, mapSizeInTilesX - 1, mapSizeInTilesY - 1);

	gameState = PLAY;
	snake.setDir(Snake::Direction::STILL); // Set initial direction to STILL

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

void Game::handleGameState(RenderWindow& window) {
	// Handle game state
	switch (gameState) {
	case PAUSED:
		std::cout << "PAUSE" << std::endl;
		showPauseMenu(window);
		break;
	case GAMEOVER:
		std::cout << "GAMEOVER" << std::endl;
		showGameOverMenu(window);
		break;
	}
}

void Game::showPauseMenu(RenderWindow& window) {
	// Implement pause menu logic here

	// window.setFramerateLimit(menuFPSLimit);
	pauseMenu.draw(window);
	window.display();

	// PAUSE MENU LOOP
	while (window.isOpen() && gameState == PAUSED) {
		Event event;
		Event lastKeyPressedEvent;

		// Block until at least one event is available
		if (window.waitEvent(event)) {
			lastKeyPressedEvent = event;

			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}

			// Drain the rest of the queue, keeping only the last KeyPressed event
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
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
					pauseMenu.moveUp();
					break;
				case Keyboard::Key::S:
					pauseMenu.moveDown();
					break;
				case Keyboard::Key::Enter:
					doPauseMenuAction(window, pauseMenu.getHighlightedIdx());
					std::cout << "Selected menu item: " << pauseMenu.getHighlightedIdx() << std::endl;
					break;
				case Keyboard::Key::Escape:
					//window.setFramerateLimit(inGameFPSLimit);
					gameState = PLAY;
					break;
				default:
					break;
				}
			}

			//std::cout << "FRAME" << std::endl;

			// Clear window
			window.clear();

			// Draw background game
			window.draw(background);
			window.draw(apple);
			window.draw(snake);

			// Draw changes
			pauseMenu.draw(window);
			window.display();

		}
	}

}

void Game::showGameOverMenu(RenderWindow& window) {

	// window.setFramerateLimit(menuFPSLimit);
	gameOverMenu.draw(window);
	window.display();

	// PAUSE MENU LOOP
	while (window.isOpen() && gameState == GAMEOVER) {
		Event event;
		Event lastKeyPressedEvent;

		// Block until at least one event is available
		if (window.waitEvent(event)) {
			lastKeyPressedEvent = event;

			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}

			// Drain the rest of the queue, keeping only the last KeyPressed event
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
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
					gameOverMenu.moveUp();
					break;
				case Keyboard::Key::S:
					gameOverMenu.moveDown();
					break;
				case Keyboard::Key::Enter:
					doGameOverMenuAction(window, gameOverMenu.getHighlightedIdx());
					break;
				case Keyboard::Key::Escape:
					gameState = PLAY;
					break;
				default:
					break;
				}
			}

			//std::cout << "FRAME" << std::endl;

			// Clear window
			window.clear();

			// Draw background game
			window.draw(background);
			window.draw(snake);
			window.draw(apple);

			// Draw changes
			gameOverMenu.draw(window);
			window.display();

		}
	}
}

void Game::doPauseMenuAction(RenderWindow& window, int chosenItemIdx) {
	switch (chosenItemIdx) {
	case 0:
		gameState = PLAY;
		break;
	case 1:
		restartGame();
		break;
	case 2:
		window.close();
		break;
	default:
		break;
	}
}

void Game::doGameOverMenuAction(RenderWindow& window, int chosenItemIdx) {
	switch (chosenItemIdx) {
	case 0:
		restartGame();
		break;
	case 1:
		window.close();
		break;
	default:
		break;
	}
}

void Game::restartGame() {
	// Reset snake and apple
	snake = Snake(tileSize, 1, 1, Color(103, 0, 255), Color(143, 0, 204));
	apple = Apple(tileSize);
	apple.placeAppleRandomly(tileSize, mapSizeInTilesX - 1, mapSizeInTilesY - 1);

	// Reset tile occupation
	for (auto& row : tiles) {
		for (auto& elem : row) {
			elem.setOccupied(false);
		}
	}

	snake.setDir(Snake::Direction::STILL);
	gameState = PLAY;
}
