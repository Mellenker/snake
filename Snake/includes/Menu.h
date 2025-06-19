#ifndef MENU_h
#define MENU_h

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu(int windowSizeX, int windowSizeY);
	void setTitle(std::string title);
	void addItem(std::string string);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void updateHighlighted(int newIdx, int oldIdx);
	sf::Text centerOrigin(sf::Text text);
private:
	int windowSizeX;
	int windowSizeY;
	sf::Text titleText;
	std::vector<sf::Text> items;
	int curItemIdx;
};


#endif