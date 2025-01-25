#include "Menu.h"

#include <SFML/Graphics.hpp>

using namespace sf;

Menu::Menu(RenderWindow& window) {
    Text gameOverText;
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 4);

    Text restartText;
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(Color::White);
    restartText.setPosition(window.getSize().x / 2 - restartText.getGlobalBounds().width / 2, window.getSize().y / 2);

    Text exitText;
    exitText.setString("Press Esc to Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(Color::White);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);

    window.draw(gameOverText);
    window.draw(restartText);
    window.draw(exitText);
}