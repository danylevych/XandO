#include <iostream>
#include <Windows.h>
#include "Core.hpp"
//#include "src/Scripts/Game.h"

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Core::Console::SetTitle(L"X AND O");
	Core::Console::ConsoleSize(25, 15);
	Core::Console::CursorVisible(false);
	Core::Console::ScrollbarVisible(false);

	//Game game;

	//while (game.MainLoop());

	return 0;
}