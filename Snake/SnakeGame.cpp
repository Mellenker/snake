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
int snakeStartX = 2;
int snakeStartY = 2;
Color snakeColorHead = Color(141, 0, 255);
Color snakeColorTail = Color(143, 0, 204);

// Window settings
const int winSizeInTilesX = 25;
const int winSizeInTilesY = 25;

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

	Sprite background(texture.getTexture());

	Snake snake(snakeStartX, snakeStartY, tileSize, snakeColorHead, snakeColorTail);

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
		int xSnake = snake.getHeadTileCoords()['x'];
		int ySnake = snake.getHeadTileCoords()['y'];

		// Current apple location
		int xApple = apple.getAppleCoords()['x'];
		int yApple = apple.getAppleCoords()['y'];

		// Check if snake reached apple
		if (xSnake == xApple && ySnake == yApple) {
			// Add score here
			snake.addSegment(tileSize, Vector2f(xSnake * tileSize, ySnake * tileSize));
			apple.placeAppleRandomly(tileSize, winSizeInTilesX - 1, winSizeInTilesY - 1);
		}

		Event event;

		// Handle events
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// Keyboard input
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Key::Escape) {
					// Pause logic
				}
				else {
					switch (event.key.code) {
					case Keyboard::Key::W:
						direction = UP;
						break;
					case Keyboard::Key::A:
						direction = LEFT;
						break;
					case Keyboard::Key::S:
						direction = DOWN;
						break;
					case Keyboard::Key::D:
						direction = RIGHT;
						break;
					default:
						break;
					}
				}
			}
		}

		// Movement
		{
			std::lock_guard<std::mutex> lock(moveMutex);
			if (canMove) {
				switch (direction) {
				case UP:
					ySnake--;
					break;
				case LEFT:
					xSnake--;
					break;
				case DOWN:
					ySnake++;
					break;
				case RIGHT:
					xSnake++;
					break;
				default:
					break;
				}

				if ((xSnake >= 0 && xSnake < winSizeInTilesX) && (ySnake >= 0 && ySnake < winSizeInTilesY) && direction != STILL) {
					snake.move(tiles[xSnake][ySnake].getPosition());
					snake.setHeadTileCoords(xSnake, ySnake);
				}
				else {
					// Game over here
				}
				canMove = false;
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