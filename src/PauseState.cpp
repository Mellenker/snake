#include "PauseState.hpp"

PauseState::PauseState(sf::RenderWindow& window, Game& game) :
    State(window),    
    m_game(game)
{
    window.setFramerateLimit(0); // Disable FPS limit in menus
}

void PauseState::processInput(Context& context) {

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

    // Ensure no busy waiting in menus
    if (const std::optional<sf::Event> ev = m_window.waitEvent()) {
        handleEvent(ev.value());
        // Drain any additional events in queue, keep latest key pressed
        while (const std::optional<sf::Event> pe = m_window.pollEvent()) {
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
            if (context.pauseMenu) context.pauseMenu->moveUp();
            break;
        case sf::Keyboard::Key::S:
            if (context.pauseMenu) context.pauseMenu->moveDown();
            break;
        case sf::Keyboard::Key::Enter:
            if (context.pauseMenu) context.pauseMenuAction = context.pauseMenu->decideAction();
            break;
        case sf::Keyboard::Key::Escape:
            context.pauseMenuAction = PauseMenu::Action::UNPAUSE;
            break;
        default:
            break;
        }
    }
}

void PauseState::update(Context& context) {
    
    switch (context.pauseMenuAction.value_or(PauseMenu::Action::NONE)) {
    case PauseMenu::Action::UNPAUSE:
        context.changeState(State::StateID::PLAY);
        break;
    case PauseMenu::Action::RESTART:
        m_game.resetGame();
        context.changeState(State::StateID::PLAY);
        break;
    case PauseMenu::Action::EXIT:
        m_window.close();
        break;
    default:
        break;  
    }
    
    context.pauseMenuAction = PauseMenu::Action::NONE; // Reset action
}

void PauseState::render(Context& context) {

	m_window.clear();
    m_game.drawObjects(m_window);
    if (context.pauseMenu) context.pauseMenu->draw(m_window);
	m_window.display();
}