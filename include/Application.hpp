#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "Utils.hpp"
#include "State.hpp"
#include "Context.hpp"
#include "Menu.hpp"

class Application {
public:
	Application();
	void runGameLoop();
private: 
	std::unique_ptr<State> createState(State::StateID id);
	void setupMenus();
	void changeState(State::StateID id);

	sf::RenderWindow m_window;
	Game m_game; 

	Menu m_pauseMenu;
	Menu m_gameOverMenu;

	Context m_context;
	std::unique_ptr<State> m_currentState;
};