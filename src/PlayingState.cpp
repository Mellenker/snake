#include "PlayingState.hpp"
#include <iostream>

PlayingState::PlayingState(sf::RenderWindow& window, Game& game) :
    State(window),
    game(game)
{}

void PlayingState::processInput(Context& Context) {
   std::cout << "PLAYING STATE!!!" << "\n"; 
}

void PlayingState::update(Context& context) {

}

void PlayingState::render() {

}