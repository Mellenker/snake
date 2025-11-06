#include "PlayState.hpp"

PlayState::PlayState(sf::RenderWindow& window, Game& game) :
    State(window),
    m_game(game),
	m_moveClock(),
	m_moveInterval(sf::seconds(0.15f))
{}

void PlayState::processInput(Context& context) {
	bool keyWasPressed = false;
    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
		if (ev->is<sf::Event::Closed>()) {
			context.closeWindow = true;
			return;
		}
        else if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
				context.keyPressed = sf::Keyboard::Key::Escape;
				keyWasPressed = true;
			}
        }
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		context.keyPressed = sf::Keyboard::Key::W;	
		keyWasPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		context.keyPressed = sf::Keyboard::Key::A;
		keyWasPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		context.keyPressed = sf::Keyboard::Key::S;
		keyWasPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		context.keyPressed = sf::Keyboard::Key::D;
		keyWasPressed = true;
	}
	if (!keyWasPressed) {
		context.keyPressed = sf::Keyboard::Key::Unknown;
	}

}

void PlayState::update(Context& context) {
	// Close window?
	if (context.closeWindow)
		m_window.close();
	// Pause?
	if (context.keyPressed == sf::Keyboard::Key::Escape) {
		context.changeState(State::StateID::PAUSE);
		context.keyPressed = sf::Keyboard::Key::Unknown; // Clear key state after handling
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