#pragma once

#include "../Dependences/Include/Core.hpp"

class ResultMenu : public Core::IMenu
{
private:
	char result;

public:
	ResultMenu();
	
	ResultMenu(char result);

private:
	virtual void Init() override;

public:
	virtual bool MainLoop() override;

	void Update();
};