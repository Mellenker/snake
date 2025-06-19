#pragma once
#include "includes/Menu.h"

class PauseMenu : public Menu {
public:
	using Menu::Menu; // Inherit constructor from Menu
	void performAction() override;
private:

};

