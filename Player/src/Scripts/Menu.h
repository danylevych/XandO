#pragma once

#include "Player.h"
#include "../../../Event/Core.hpp"

class Menu : public Core::IMenu
{
public:
	Menu();

private:
	virtual void Init() override;

	void Update();

public:
	virtual bool MainLoop() override;
};

