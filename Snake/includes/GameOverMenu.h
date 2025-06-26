#pragma once
#include "includes/Menu.h"

class GameOverMenu : public Menu {
public:
	GameOverMenu(int windowSizeX, int windowSizeY);
	void performAction() override;
private:

};