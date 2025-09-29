#pragma once
#include <SFML/Graphics.hpp>
#include "../includes/Game.hpp"
#include "../includes/Utils.hpp"
#include "../includes/PauseMenu.hpp"
#include "../includes/GameOverMenu.hpp"

class Application {
public:
	Application();
	void runGameLoop();
	sf::Keyboard::Key processEvent();
	sf::Event checkForLastKeyPressedEvent(sf::Event event);
	void processPauseMenuInput(sf::Keyboard::Key key);
	void processGameOverMenuInput(sf::Keyboard::Key key);
	void update(sf::Keyboard::Key keyPressed);
	void updatePlayState(sf::Keyboard::Key keyPressed);
	void updatePauseState(sf::Keyboard::Key keyPressed);
	void updateGameOverState(sf::Keyboard::Key keyPressed);
	void render();


private:
	Game game;

	Utils::GameState gameState;
	PauseMenu pauseMenu;
	PauseMenu::Action pauseMenuAction = PauseMenu::Action::NONE;
	GameOverMenu gameOverMenu;
	GameOverMenu::Action gameOverMenuAction = GameOverMenu::Action::NONE;

	static constexpr int maxFPS = 4;

	sf::RenderWindow window;
};