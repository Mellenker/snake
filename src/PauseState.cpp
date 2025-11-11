#include "PauseState.hpp"
#include "PlayState.hpp"

PauseState::PauseState(sf::RenderWindow& window, Game& game, Menu& menu) :
    State(window),    
    m_game(game),
    m_menu(menu)
{}

void PauseState::processInput(Context& context) {
    while (const std::optional<sf::Event> ev = m_window.pollEvent()) {
		if (ev->is<sf::Event::Closed>()) {
			context.closeWindow = true;
			return;
		}
        else if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
			switch(keyPressed->scancode) {
				case sf::Keyboard::Scancode::Escape:
				case sf::Keyboard::Scancode::W:
				case sf::Keyboard::Scancode::S:
				case sf::Keyboard::Scancode::Enter:
					context.keyPressed = keyPressed->scancode; 
				default:
					break;
			}
       }
    }
}

void PauseState::update(Context& context) {
    if (context.closeWindow)
        m_window.close();
        
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
    case sf::Keyboard::Scancode::Escape:
        context.changeState(State::StateID::PLAY);
        break;
    }
    context.keyPressed = sf::Keyboard::Scancode::Unknown;
}

void PauseState::render(Context& context) {
	m_window.clear();
    m_game.drawObjects(m_window);
    m_menu.draw(m_window);
	m_window.display();
}