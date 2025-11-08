#include "PauseState.hpp"
#include "PlayState.hpp"

PauseState::PauseState(sf::RenderWindow& window, Game& game, Menu& menu) :
    State(window),    
    m_game(game),
    m_menu(menu)
{}

void PauseState::processInput(Context& context) {
	std::optional<sf::Event> lastKeyPressedEvent = std::nullopt;

	auto handleEvent = [&](const sf::Event& ev) {
		if (ev.is<sf::Event::Closed>()) {
			context.closeWindow = true;
			return;
		}
		if (ev.is<sf::Event::KeyPressed>()) {
			lastKeyPressedEvent = ev;
		}
	};

    // Block until event
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
            context.keyPressed = sf::Keyboard::Key::W;
            break;
        case sf::Keyboard::Key::S:
            context.keyPressed = sf::Keyboard::Key::S;
            break;
        case sf::Keyboard::Key::Enter:
            context.keyPressed = sf::Keyboard::Key::Enter;
            break;
        case sf::Keyboard::Key::Escape:
            context.keyPressed = sf::Keyboard::Key::Escape;
            break;
        default:
            break;
        }
    }
}

void PauseState::update(Context& context) {
    if (context.closeWindow)
        m_window.close();
        
    switch (context.keyPressed) {
    case sf::Keyboard::Key::W:
        m_menu.moveUp();
        break;  
    case sf::Keyboard::Key::S:
        m_menu.moveDown();    
        break;  
    case sf::Keyboard::Key::Enter:
        m_menu.executeSelectedAction();
        break;  
    case sf::Keyboard::Key::Escape:
        context.changeState(State::StateID::PLAY);
        break;
    }
    context.keyPressed = sf::Keyboard::Key::Unknown;
}

void PauseState::render(Context& context) {
	m_window.clear();
    m_game.drawObjects(m_window);
    m_menu.draw(m_window);
	m_window.display();
}