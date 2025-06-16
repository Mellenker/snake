#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

RectangleShape menuPanel;

Menu::Menu(RenderWindow& window) {
	menuPanel.setFillColor(Color::White);
	menuPanel.setSize(Vector2f(window.getSize().x / 3, window.getSize().y / 2));
	menuPanel.setPosition(Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	std::cout << std::to_string(window.getSize().x / 3) << std::endl;
}

void Menu::draw(RenderWindow& window) {
	window.draw(menuPanel);
}
