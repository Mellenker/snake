#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <mutex>
#include "includes/Snake.h"
#include "includes/Tile.h"

using namespace std;
using namespace sf;

// Tile settings
int tileSize = 30;
Color tileColor1 = Color(0, 132, 9);
Color tileColor2 = Color(0, 118, 9);

// Window settings
const int winSizeInTilesX = 25;
const int winSizeInTilesY = 25;

// Movement control
bool canMove = false;
mutex moveMutex;

void movementTimer() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(200)); // Adjust the interval as needed
        lock_guard<mutex> lock(moveMutex);
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

    Snake snake(10, 10, tileSize);

    enum Direction { UP, LEFT, RIGHT, DOWN, STILL };
    enum Direction direction = STILL;

    // Start the movement timer thread
    thread timerThread(movementTimer);
    timerThread.detach();

    // Game loop (Runs once each frame)
    while (window.isOpen()) {
        
        // Current snake position
        int x = snake.getHeadTileCoords()['x'];
        int y = snake.getHeadTileCoords()['y'];
        
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
            lock_guard<mutex> lock(moveMutex);
            if (canMove) {
                
                switch (direction) {
                case UP:
                    y--;
                    break;
                case LEFT:
                    x--;
                    break;
                case DOWN:
                    y++;
                    break;
                case RIGHT:
                    x++;
                    break;
                default:
                    break;
                }
                
                if ((x >= 0 && x < winSizeInTilesX) && (y >= 0 && y < winSizeInTilesY)) {
                    snake.move(tiles[x][y].getPosition());
                    snake.setHeadTileCoords(x, y);
                }
                else {
                    // Game over here
                }
                canMove = false;
            }
        }

        window.clear();
        window.draw(background);
        snake.draw(window);
        //window.draw(apple);

        window.display();
    }

    return 0;
}