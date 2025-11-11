#include "PlayState.hpp"
#include <iostream>

PlayState::PlayState(sf::RenderWindow& window, Game& game) :
    State(window),
    m_game(game),
	m_moveClock(),
	m_moveInterval(sf::seconds(0.15f))
{}

void PlayState::processInput(Context& context) {
    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
		if (ev->is<sf::Event::Closed>()) {
			context.closeWindow = true;
			return;
		}
        else if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
			switch(keyPressed->scancode) {
				case sf::Keyboard::Scancode::Escape:
					context.keyPressed = keyPressed->scancode;
					break;
				case sf::Keyboard::Scancode::W:
				case sf::Keyboard::Scancode::A:
				case sf::Keyboard::Scancode::S:
				case sf::Keyboard::Scancode::D:
					// Keep maximum 2 keys in buffer
					if (context.movementInputBuffer.size() < 2) {
						context.movementInputBuffer.push(keyPressed->scancode);
					}
				default:
					break;
			}
       }
    }
}

void PlayState::update(Context& context) {
	// Close window?= 
	if (context.closeWindow)
		m_window.close();
	// Pause?
	if (context.keyPressed == sf::Keyboard::Scancode::Escape) {
		context.changeState(State::StateID::PAUSE);
		context.keyPressed = sf::Keyboard::Scancode::Unknown; // Clear key state after handling
	}
	// Movement
	else if (m_moveClock.getElapsedTime() > m_moveInterval) {
		sf::Keyboard::Scancode keyCode = sf::Keyboard::Scancode::Unknown;
		if (!context.movementInputBuffer.empty()) {
			keyCode = context.movementInputBuffer.front();
			context.movementInputBuffer.pop();
		}
		m_moveClock.restart();

		m_game.updateSnakeDir(keyCode);

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