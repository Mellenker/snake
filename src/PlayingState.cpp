#include "PlayingState.hpp"
#include <iostream>

PlayingState::PlayingState(sf::RenderWindow& window, Game& game) :
    State(window),
    game(game)
{}

void PlayingState::processInput(Context& context) {
    
	std::optional<sf::Event> lastKeyPressedEvent = std::nullopt;

	auto handleEvent = [&](const sf::Event& ev) {
		if (ev.is<sf::Event::Closed>()) {
			window.close();
			return;
		}
		if (ev.is<sf::Event::KeyPressed>()) {
			lastKeyPressedEvent = ev;
		}
	};

    while (const std::optional<sf::Event> ev = window.pollEvent()) {
        handleEvent(ev.value());
    }

	if (!lastKeyPressedEvent) {
		context.keyPressed = sf::Keyboard::Key::Unknown; // No key was pressed
	}
	else {
		// Process only latest keyboard input
		sf::Keyboard::Key keyCode = lastKeyPressedEvent->getIf<sf::Event::KeyPressed>()->code;
        
        if (keyCode == sf::Keyboard::Key::Escape) {
            context.changeState(std::make_unique<PauseState>(window, game));
        }
        else {
            context.keyPressed = keyCode;
        }
    }
}

void PlayingState::update(Context& context) {
	game.forwardSnakeInput(context.keyPressed);

	// Returns true if illegal move is attempted
	if (game.tryUpdateSnakeState()) {
        context.changeState(std::make_unique<GameOverState>(window, game));    
    }

}

void PlayingState::render(Context& context) {
	window.clear();
    game.drawObjects(window);
	window.display();
}