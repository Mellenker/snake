#include "PauseState.hpp"

PauseState::PauseState(PauseMenu& menu, Game& game, sf::RenderWindow& window) :
    State(window),    
    menu(menu),
    game(game)
{}

void PauseState::processInput(Context& context) {

    switch (context.keyPressed) {
    case sf::Keyboard::Key::W:
        menu.moveUp();
        break;
    case sf::Keyboard::Key::S:
        menu.moveDown();
        break;
    case sf::Keyboard::Key::Enter:
        context.action = menu.decideAction();
        break;
    case sf::Keyboard::Key::Escape:
        context.action = PauseMenu::Action::UNPAUSE;
        break;
    default:
        break;
    }
}

void PauseState::update(Context& context) {
    
    switch (context.action.value()) {
    case PauseMenu::Action::UNPAUSE:
        context.changeState(std::make_unique<PlayingState>(window, game));
        break;
    case PauseMenu::Action::RESTART:
        game.resetGame();
        context.changeState(std::make_unique<PlayingState>(window, game));
        break;
    case PauseMenu::Action::EXIT:
        window.close();
        break;
    default:
        break;  
    }
    
    context.action = PauseMenu::Action::NONE; // Reset action
}

void PauseState::render() {

	window.clear();
    game.drawObjects(window);
    menu.draw(window);
}