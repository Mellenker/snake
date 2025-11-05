#include "PlayState.hpp"

PlayState::PlayState(sf::RenderWindow& window, Game& game) :
    State(window),
    m_game(game),
	m_moveClock(),
	m_moveInterval(sf::seconds(0.15f))
{}

void PlayState::processInput(Context& context) {
    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
		if (ev->is<sf::Event::Closed>()) {
			m_window.close(); // Put into context and handle in update instead?
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
		context.keyPressed = sf::Keyboard::Key::Escape;
	}
}

void PlayState::update(Context& context) {
	// Pause
	if (context.keyPressed == sf::Keyboard::Key::Escape) {
		context.changeState(State::StateID::PAUSE);
	}
	// Movement
	else if (m_moveClock.getElapsedTime() > m_moveInterval) {
		m_moveClock.restart();

		m_game.updateSnakeDir(context.keyPressed);

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