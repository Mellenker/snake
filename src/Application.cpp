#include "Application.hpp"

#include <iostream>

Application::Application() : 
	m_pauseMenuAction(PauseMenu::Action::NONE),
	m_gameOverMenuAction(GameOverMenu::Action::NONE),
	m_inGameFpsLimit(4),
	m_currentState(createState(State::StateID::PLAY))
{
	// Build window
	m_window.create(sf::VideoMode({ Utils::g_mapSizeInTilesX * Utils::g_tileSize, Utils::g_mapSizeInTilesY * Utils::g_tileSize }), "Snake Game");
	m_window.setTitle("Snake");
	m_window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses
	m_window.setFramerateLimit(m_inGameFpsLimit);

	// Build context
	m_context.pauseMenu = &m_pauseMenu;
	m_context.gameOverMenu = &m_gameOverMenu;
	m_context.changeState = [this](State::StateID id) {
		this->changeState(id);
	};
}

void Application::runGameLoop() {

	while (m_window.isOpen()) {
		m_currentState->processInput(m_context);
		m_currentState->update(m_context);
		m_currentState->render(m_context);
	}
}

std::unique_ptr<State> Application::createState(State::StateID id) {
	switch(id) {
		case State::StateID::PLAY:
			return std::make_unique<PlayState>(m_window, m_game, m_inGameFpsLimit);
			break;
		case State::StateID::PAUSE:
			return std::make_unique<PauseState>(m_window, m_game);
			break;
		case State::StateID::GAME_OVER:
			return std::make_unique<GameOverState>(m_window, m_game);
			break;
		default:
			throw std::runtime_error("Unknown state ID");
	}
}

void Application::changeState(State::StateID id) {
	m_currentState = createState(id);
}