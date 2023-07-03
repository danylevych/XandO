#pragma once

#include "../../../Event/Core.hpp"

class ResultMenu : public Core::IMenu
{
public:
	ResultMenu();

	ResultMenu(Core::Wallpaper&& wall);

	ResultMenu(const Core::Wallpaper& wall);

private:
	void Update();

	virtual void Init() override;

public:
	virtual bool MainLoop() override;
};

