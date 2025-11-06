#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "Utils.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "State.hpp"
#include "Context.hpp"

class Application {
public:
	Application();
	void runGameLoop();
private: 
	std::unique_ptr<State> createState(State::StateID id);
	void changeState(State::StateID id);

	sf::RenderWindow m_window;
	Game m_game; 

	PauseMenu m_pauseMenu;
	PauseMenu::Action m_pauseMenuAction;
	GameOverMenu m_gameOverMenu;
	GameOverMenu::Action m_gameOverMenuAction;

	Context m_context;
	std::unique_ptr<State> m_currentState;
};