#include "PlayState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

PlayState::PlayState(sf::RenderWindow& window, Game& game, int inGameFpsLimit) :
    State(window),
    m_game(game)
{
	m_window.setFramerateLimit(inGameFpsLimit);
}

void PlayState::processInput(Context& context) {
	std::optional<sf::Event> lastKeyPressedEvent = std::nullopt;
	auto handleEvent = [&](const sf::Event& ev) {
		if (ev.is<sf::Event::Closed>()) {
			m_window.close();
			return;
		}
		if (ev.is<sf::Event::KeyPressed>()) {
			lastKeyPressedEvent = ev;
		}
	};

    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
        handleEvent(ev.value());
    }

	if (!lastKeyPressedEvent) {
		context.keyPressed = sf::Keyboard::Key::Unknown; // No key was pressed
	}
	else {
		// Process only latest keyboard input
		sf::Keyboard::Key keyCode = lastKeyPressedEvent->getIf<sf::Event::KeyPressed>()->code;
		
        if (keyCode == sf::Keyboard::Key::Escape) {
            context.changeState(State::StateID::PAUSE);
        }
        else {
            context.keyPressed = keyCode;
        }
    }
}

void PlayState::update(Context& context) {
	m_game.forwardSnakeInput(context.keyPressed);

	// Returns true if illegal move is attempted
	if (m_game.tryUpdateSnakeState()) {
        context.changeState(State::StateID::GAME_OVER);    
    }

}

void PlayState::render(Context& context) {
	m_window.clear();
    m_game.drawObjects(m_window);
	m_window.display();
}