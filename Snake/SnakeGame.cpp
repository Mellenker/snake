#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <mutex>

#include "includes/Snake.h"
#include "includes/Tile.h"
#include "includes/Apple.h"

using namespace sf;

// Tile settings
int tileSize = 30;
Color tileColor1 = Color(0, 132, 9);
Color tileColor2 = Color(0, 118, 9);

// Snake settings
int snakeStartX = 4;
int snakeStartY = 4;
Color colorSnakeHead = Color(103, 0, 255);
Color colorSnakeTail = Color(143, 0, 204);

// Window settings
const int winSizeInTilesX = 15;
const int winSizeInTilesY = 15;

// Movement control
bool canMove = false;
std::mutex moveMutex;

void movementTimer() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Adjust the interval as needed
		std::lock_guard<std::mutex> lock(moveMutex);
		canMove = true;
	}
}

int main() {
	RenderWindow window(VideoMode(winSizeInTilesX * tileSize, winSizeInTilesY * tileSize), "SnakeGame");

	RenderTexture texture;
	texture.create(winSizeInTilesX * tileSize, winSizeInTilesY * tileSize);

	Tile tiles[winSizeInTilesX][winSizeInTilesY];

	// Populate background with tiles
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

	if (!tiles[9][9].isOccupied())
		std::cout << "SHIIIT" << std::endl;

	Sprite background(texture.getTexture());

	Snake snake(snakeStartX, snakeStartY, tileSize, colorSnakeHead, colorSnakeTail);

	Apple apple(tileSize);
	apple.placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);

	enum Direction { UP, LEFT, RIGHT, DOWN, STILL };
	enum Direction direction = STILL;

	// Start the movement timer thread
	std::thread timerThread(movementTimer);
	timerThread.detach();

	// Game loop (Runs once each frame)
	while (window.isOpen()) {

		// Current snake position
		int xSnakeHead = snake.getHeadTileCoords()['x'];
		int ySnakeHead = snake.getHeadTileCoords()['y'];

		// Current apple location
		int xApple = apple.getAppleCoords()['x'];
		int yApple = apple.getAppleCoords()['y'];

		// Check if snake reached apple
		if (xSnakeHead == xApple && ySnakeHead == yApple) {
			// Add score here
			snake.addSegment();
			apple.placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);
		}

		Event event;

		// Handle events
		bool firstLoopThisFrame = true;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// Keyboard input
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Key::Escape) {
					// Pause logic
				}
				else if (firstLoopThisFrame){
					switch (event.key.code) {
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
				}
			}
			firstLoopThisFrame = false;
		}

		// Movement
		{
			std::lock_guard<std::mutex> lock(moveMutex);
			if (canMove) {
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
				if (!((xSnakeHead >= 0 && xSnakeHead < winSizeInTilesX) && (ySnakeHead >= 0 && ySnakeHead < winSizeInTilesY) && direction != STILL)) {
					// Game over here
				}
				else if (tiles[xSnakeHead][ySnakeHead].isOccupied()) {
					// Game over here
					std::cout << xSnakeHead << std::endl;
					std::cout << ySnakeHead << std::endl;
					std::cout << direction << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(120000));
	
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

					canMove = false;
				}
			}
		}

		window.clear();

		// Draw game objects
		window.draw(background);
		snake.draw(window);
		apple.draw(window);

		window.display();
	}

	return 0;
}