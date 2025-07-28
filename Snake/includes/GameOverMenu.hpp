#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Menu.hpp"
#include <functional>

class GameOverMenu : public Menu {
public:
	GameOverMenu(int windowSizeX, int windowSizeY);
	void performAction(sf::RenderWindow& window, int selectedIdx, std::function<void()> restartGame);
private:

};