#include <SFML/Graphics.hpp>
#include <iostream>	
#include "includes/Application.hpp"

using namespace sf;

// SOMETHING IS WRONG WITH HOW SFML OBJECTS ARE DESTRUCTED

int main() {

	Application app;
	app.runGameLoop();
	return 0;
}