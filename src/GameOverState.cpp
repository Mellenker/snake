#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow& window, Game& game, Menu& menu) :
    State(window),    
    m_game(game),
    m_menu(menu)
{
    // Change snake face texture
    m_game.updateSnakeFace("assets/textures/snake_face_dead.png");
}

void GameOverState::processInput(Context& context) {
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

    // Ensure no busy waiting in menus
    if (const std::optional<sf::Event> ev = m_window.waitEvent()) {
        handleEvent(ev.value());
        // Drain any additional events in queue, keep latest key pressed
        while (const std::optional<sf::Event> pe = m_window.pollEvent()) {
            handleEvent(pe.value());
        }
    }

	if (!lastKeyPressedEvent) {
		context.keyPressed = sf::Keyboard::Scancode::Unknown; // No key was pressed
	}
	else {
		// Process only latest keyboard input
		sf::Keyboard::Scancode keyCode = lastKeyPressedEvent->getIf<sf::Event::KeyPressed>()->scancode;
        switch (keyCode) {
        case sf::Keyboard::Scancode::W:
            context.keyPressed = sf::Keyboard::Scancode::W;
            break;
        case sf::Keyboard::Scancode::S:
            context.keyPressed = sf::Keyboard::Scancode::S;
            break;
        case sf::Keyboard::Scancode::Enter:
            context.keyPressed = sf::Keyboard::Scancode::Enter;
            break;
        default:
            break;
        }
    }
}

void GameOverState::update(Context& context) {
    // Close window?
	if (context.closeWindow)
		m_window.close();
    
    // Handle menu navigation and actions
    switch (context.keyPressed) {
    case sf::Keyboard::Scancode::W:
        m_menu.moveUp();
        break;  
    case sf::Keyboard::Scancode::S:
        m_menu.moveDown();    
        break;  
    case sf::Keyboard::Scancode::Enter:
        m_menu.executeSelectedAction();
        break;  
    }
    
    context.keyPressed = sf::Keyboard::Scancode::Unknown; // Reset key state after handling
}

void GameOverState::render(Context& context) {
	m_window.clear();
    m_game.drawObjects(m_window);
    m_menu.draw(m_window);
	m_window.display();
}