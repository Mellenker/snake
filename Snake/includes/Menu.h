#pragma once  

#include <SFML/Graphics.hpp>  
// Abstract Class  
class Menu {
public:
	Menu(int windowSizeX, int windowSizeY);
	void setTitle(std::string title);
	void addItem(std::string string);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void updateHighlighted(int newIdx, int oldIdx);
	virtual void performAction() = 0; // Mark as pure virtual to enforce implementation in derived classes  
	void centerOrigin(sf::Text& text);
	int getHighlightedIdx();
protected:
	int windowSizeX;
	int windowSizeY;
	sf::Text titleText;
	std::vector<sf::Text> items;
	int highlightedIdx;
};