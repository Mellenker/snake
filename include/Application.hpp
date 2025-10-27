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
	sf::RenderWindow m_window;
	Game m_game; 

	PauseMenu m_pauseMenu;
	PauseMenu::Action m_pauseMenuAction;
	GameOverMenu m_gameOverMenu;
	GameOverMenu::Action m_gameOverMenuAction;

	int m_maxFPS = 2;

	Context m_context;
	std::unique_ptr<State> m_currentState;
};