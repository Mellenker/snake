#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Snake{
public:
    Snake();
    void move(sf::Keyboard::Key key);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getHeadPosition();
    void collideWallY();
    void collideWallX();


private:
    std::vector<sf::RectangleShape> body;
    sf::Vector2f direction;
};

#endif
