#include "includes/Game.h"
#include <iostream>

using namespace sf;

/*
What should be handled:
- Game states: PLAY, PAUSED, GAMEOVER
- PAUSE MENU, GAMEOVER MENU
*/

Game::Game()
	: snake(tileSize, 1, 1, Color::Blue, Color::White), apple(tileSize), tileColor1(Color(0, 132, 9)), tileColor2(Color(0, 118, 9))
{
	// Setup background
	spawnTiles(texture);
	background = Sprite(texture.getTexture());
}

void Game::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(apple);
	window.draw(snake);

	std::cout << "DRAW!\n";
}

// Handle ingame keyboard input
void Game::handleKeyboardInput(Keyboard::Key keyPressed) {
	switch (keyPressed) {
	case Keyboard::Key::Escape:
		std::cout << "ESCAPE" << std::endl;
		gameState = PAUSED;
		break;
	case Keyboard::Key::W:
		if (currDir != DOWN) {
			std::cout << "UP" << std::endl;
			currDir = UP;
		}
		break;
	case Keyboard::Key::A:
		if (currDir != RIGHT) {
			std::cout << "UP" << std::endl;
			currDir = LEFT;
		}
		break;
	case Keyboard::Key::S:
		if (currDir != UP) {
			std::cout << "DOWN" << std::endl;
			currDir = DOWN;
		}
		break;
	case Keyboard::Key::D:
		if (currDir != LEFT) {
			std::cout << "RIGHT" << std::endl;
			currDir = RIGHT;
		}
		break;
	default:
		break;
	}
	return;
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
			tile.draw(texture);
			colorFlag = !colorFlag;
		}
		xPos = 0; // Reset x position after each row
		yPos += tileSize;
	}
}



