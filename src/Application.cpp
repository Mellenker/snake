#include "Application.hpp"

#include <iostream>

Application::Application() : 
	m_pauseMenuAction(PauseMenu::Action::NONE),
	m_gameOverMenuAction(GameOverMenu::Action::NONE),
	m_currentState(std::make_unique<PlayingState>(m_window, m_game))
{
	// Build window
	m_window.create(sf::VideoMode({ Utils::g_mapSizeInTilesX * Utils::g_tileSize, Utils::g_mapSizeInTilesY * Utils::g_tileSize }), "Snake Game");
	m_window.setTitle("Snake");
	m_window.setFramerateLimit(m_maxFPS);
	m_window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses

	// Build context
	m_context.pauseMenu = &m_pauseMenu;
	m_context.gameOverMenu = &m_gameOverMenu;
	m_context.changeState = [this](std::unique_ptr<State> newState) {
		this->changeState(std::move(newState));
	};
}

void Application::runGameLoop() {

	while (m_window.isOpen()) {
		m_currentState->processInput(m_context);
		m_currentState->update(m_context);
		m_currentState->render(m_context);
	}
}

void Application::changeState(std::unique_ptr<State> newState) {
	m_currentState = std::move(newState);
}