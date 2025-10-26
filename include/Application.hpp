#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include "Game.hpp"
#include "Utils.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "State.hpp"
#include "PlayingState.hpp"
#include "Context.hpp"

class Application {
public:
	Application();
	void runGameLoop();
	void changeState(std::unique_ptr<State> newState);

private: 
	sf::RenderWindow window;
	Game game; 

	PauseMenu pauseMenu;
	PauseMenu::Action pauseMenuAction;
	GameOverMenu gameOverMenu;
	GameOverMenu::Action gameOverMenuAction;

	static constexpr int maxFPS = 4;

	Context context;
	std::unique_ptr<State> currentState;
};