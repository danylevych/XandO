#include <iostream>
#include <Windows.h>
#include "Core.hpp"
#include "src/Scripts/Menu.h"
#include "src/Scripts/Game.h"

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Core::Console::SetTitle(L"X AND O");
	
	Menu menu;
	while (menu.MainLoop());

	//Game game;

	//while (game.MainLoop());

	return 0;
}