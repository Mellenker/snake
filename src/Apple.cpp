#include "Apple.hpp"
#include "Utils.hpp"
#include "Colors.hpp"

Apple::Apple()
	: m_shape(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize)),
	m_texture("assets/textures/apple.png")
{
	m_texture.setSmooth(true);
	m_shape.setTexture(&m_texture);
}

void Apple::setPosition(sf::Vector2f pos) {
	m_shape.setPosition(pos);
}

sf::Vector2f Apple::getPosition() {
	return m_shape.getPosition();
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_shape, states);
};