#pragma once
#include "includes/Menu.h"

class GameOverMenu: public Menu{
public:
	using Menu::Menu; // Inherit constructor from Menu
	void performAction() override;
private:

};