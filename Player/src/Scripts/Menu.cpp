#include "Menu.h"

#include <iostream>


Menu::Menu()
	: IMenu()
{
	Init();
};

void Menu::Init()
{
	Core::Console::ConsoleSize(25, 16);
	Core::Console::CursorVisible(false);
	Core::Console::ScrollbarVisible(false);

	this->user = Core::Color::DARK_RED;
	this->application = Core::Color::GREEN;

	wall = Core::Wallpaper("data/Walls/MenuWall.txt");

	Core::BuildButton build;

	build.CreateButton();
	build.SetText("play", Core::Fonts::FULL);
	build.SetX(5).SetY(6);
	build.SetCommand([]()
		{
			Core::Console::Clear();
			Player player{"localhost", "666"};
		});
	buttons.push_back(*build.GetButton().release());

	build.CreateButton();
	build.SetText("exit", Core::Fonts::FULL);
	build.SetX(5).SetY(10);
	build.SetCommand([]()
		{
			Core::Console::Clear();
			std::exit(0);
		});
	buttons.push_back(*build.GetButton().release());
}

bool Menu::MainLoop()
{
	Core::Event event;
	Core::KeyEvent* key = nullptr;

	static bool firstCalling = true;
	if (firstCalling)
	{
		Update();
		firstCalling = false;
	}

	if (Core::EventManager::PollKeyEvent(event));
	{
		IMenu::CheckUserInput(event);
		key = Core::EventManager::ParseKeyEvent(event);

		if (key)
		{
			Update();
		}
	}

	return true;
}

void Menu::Update()
{
	Core::Console::SetCursorPosition(0, 0);
	std::cout << *this;
}