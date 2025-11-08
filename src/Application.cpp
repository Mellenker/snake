#include "Application.hpp"
#include <optional>
#include "PlayState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

Application::Application() : 
	m_pauseMenu("Paused"),
	m_gameOverMenu("Game Over")
{
	// Build window
	m_window.create(sf::VideoMode({ Utils::g_mapSizeInTilesX * Utils::g_tileSize, Utils::g_mapSizeInTilesY * Utils::g_tileSize }), "Snake Game");
	m_window.setTitle("Snake");
	m_window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presse

	// Set window icon
	sf::Image image;
	if (image.loadFromFile("assets/textures/snake_face_alive.png")) {
		m_window.setIcon(image.getSize(), image.getPixelsPtr());
	}

	// Allow those with access to context to change state
	m_context.changeState = [this](State::StateID id) {
		this->changeState(id);
	};

	setupMenus();

	m_currentState = createState(State::StateID::PLAY);
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
			return std::make_unique<PlayState>(m_window, m_game);
			break;
		case State::StateID::PAUSE:
			return std::make_unique<PauseState>(m_window, m_game, m_pauseMenu);
			break;
		case State::StateID::GAME_OVER:
			return std::make_unique<GameOverState>(m_window, m_game, m_gameOverMenu);
			break;
		default:
			throw std::runtime_error("Unknown state ID");
	}
}

void Application::changeState(State::StateID id) {
	m_currentState = createState(id);
}

void Application::setupMenus() {
    // Setup pause menu
    m_pauseMenu.addMenuItem("Unpause", [&]() {
        m_context.changeState(State::StateID::PLAY);
    });
    
    m_pauseMenu.addMenuItem("Restart", [&]() {
        m_game.resetGame();
        m_context.changeState(State::StateID::PLAY);
    });
    
    m_pauseMenu.addMenuItem("Exit", [&]() {
        m_window.close();
    });

    // Setup game over menu
    m_gameOverMenu.addMenuItem("Restart", [&]() {
        m_game.resetGame();
        m_context.changeState(State::StateID::PLAY);
    });
    
    m_gameOverMenu.addMenuItem("Exit", [&]() {
        m_window.close();
    });
}