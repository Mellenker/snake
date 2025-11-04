#include "PlayState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

PlayState::PlayState(sf::RenderWindow& window, Game& game) :
    State(window),
    m_game(game),
	m_moveClock(),
	m_moveInterval(sf::seconds(0.2f))
{}

void PlayState::processInput(Context& context) {
    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
		if (ev->is<sf::Event::Closed>()) {
			m_window.close();
			return;
		}
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		context.keyPressed = sf::Keyboard::Key::W;	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		context.keyPressed = sf::Keyboard::Key::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		context.keyPressed = sf::Keyboard::Key::S;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		context.keyPressed = sf::Keyboard::Key::D;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		context.changeState(State::StateID::PAUSE);
	}
}

void PlayState::update(Context& context) {
	if (m_moveClock.getElapsedTime() > m_moveInterval) {
		m_moveClock.restart();
	
		m_game.forwardSnakeInput(context.keyPressed);

		// Returns true if illegal move is attempted
		if (m_game.tryUpdateSnakeState()) {
			context.changeState(State::StateID::GAME_OVER);    
		}
	}
}

void PlayState::render(Context& context) {
	m_window.clear();	
	m_game.drawObjects(m_window);
	m_window.display();
}