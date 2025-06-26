#pragma once
#include "includes/Menu.h"

class PauseMenu : public Menu {
public:
	PauseMenu(int windowSizeX, int windowSizeY);
	void performAction() override;
private:

};

