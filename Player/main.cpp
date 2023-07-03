#include <iostream>

#include "src/Scripts/Player.h"
#include "src/Scripts/Menu.h"
#include <Windows.h>
#include "../Event/Core.hpp"


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Core::Console::SetTitle(L"X AND O");

	Menu menu;
	while (menu.MainLoop());
}