#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include "includes/Snake.h"
#include "includes/Tile.h"

using namespace std;
using namespace sf;

// Tile settings
int tileSize = 30;
Color tileColor1 = Color(0, 132, 9);
Color tileColor2 = Color(0, 118, 9);

// Window settings
const int winSizeX = 25;
const int winSizeY = 25;

int main() {
    RenderWindow window(VideoMode(winSizeX * tileSize, winSizeY * tileSize), "SnakeGame");
    Snake snake;


    RenderTexture texture;
    texture.create(winSizeX * tileSize, winSizeY * tileSize);

    Tile tiles[winSizeX][winSizeY];

    // Populate background with tiles
    int xPos = 0;
    int yPos = 0;
	bool colorFlag = true; // Flag to alternate colors
    for (int yIt = 0; yIt < winSizeY; yIt++) {
        for (int xIt = 0; xIt < winSizeX; xIt++) {
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

    // Game loop (Runs onece each frame)
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Handle one-time actions (Pause maybe?)
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Key::Escape:
                        cout << "PAUSE" << endl;
                        break;
                }
            }
        }

        // Player movement
        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			snake.move(Keyboard::Key::W);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            snake.move(Keyboard::Key::A);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            snake.move(Keyboard::Key::S);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            snake.move(Keyboard::Key::D);
        }

        window.clear();
		window.draw(background);
        snake.draw(window);
        //window.draw(apple);

        window.display();
    }

    return 0;
}