
#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow& window, Game& game) :
    State(window),    
    game(game)
{}

void GameOverState::processInput(Context& context) {

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

    // Ensure no busy waiting in menus
    if (const std::optional<sf::Event> ev = window.waitEvent()) {
        handleEvent(ev.value());
        // Drain any additional events in queue, keep latest key pressed
        while (const std::optional<sf::Event> pe = window.pollEvent()) {
            handleEvent(pe.value());
        }
    }

	if (!lastKeyPressedEvent) {
		context.keyPressed = sf::Keyboard::Key::Unknown; // No key was pressed
	}
	else {
		// Process only latest keyboard input
		sf::Keyboard::Key keyCode = lastKeyPressedEvent->getIf<sf::Event::KeyPressed>()->code;
        switch (keyCode) {
        case sf::Keyboard::Key::W:
            if (context.gameOverMenu) context.gameOverMenu->moveUp();
            break;
        case sf::Keyboard::Key::S:
            if (context.gameOverMenu) context.gameOverMenu->moveDown();
            break;
        case sf::Keyboard::Key::Enter:
            if (context.gameOverMenu) context.gameOverMenuAction = context.gameOverMenu->decideAction();
            break;
        default:
            break;
        }
    }
}

void GameOverState::update(Context& context) {
    
    switch (context.gameOverMenuAction.value_or(GameOverMenu::Action::NONE)) {
    case GameOverMenu::Action::RESTART:
        game.resetGame();
        context.changeState(std::make_unique<PlayingState>(window, game));
        break;
    case GameOverMenu::Action::EXIT:
        window.close();
        break;
    default:
        break;  
    }
    
    context.gameOverMenuAction = GameOverMenu::Action::NONE; // Reset action
}

void GameOverState::render(Context& context) {

	window.clear();
    game.drawObjects(window);
    if (context.gameOverMenu) context.gameOverMenu->draw(window);
	window.display();
}