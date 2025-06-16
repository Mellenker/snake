#ifndef MENU_h
#define MENU_h

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape menuPanel;
};

#endif