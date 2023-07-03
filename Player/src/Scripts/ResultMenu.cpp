#include "ResultMenu.h"

#include <iostream>


ResultMenu::ResultMenu()
	:IMenu()
{
	Init();
}

ResultMenu::ResultMenu(Core::Wallpaper&& wall)
	:IMenu()
{
	this->wall = wall;
	Init();
}

ResultMenu::ResultMenu(const Core::Wallpaper& wall)
	:IMenu()
{
	this->wall = wall;
	Init();
}

void ResultMenu::Init()
{
	Core::Console::ConsoleSize(25, 16);
	Core::Console::CursorVisible(false);
	Core::Console::ScrollbarVisible(false);

	this->user = Core::Color::DARK_RED;
	this->application = Core::Color::GREEN;

	Core::BuildButton build;

	build.CreateButton();
	build.SetText("back", Core::Fonts::FULL);
	build.SetX(5).SetY(10);
	build.SetCommand([]() {});  // This is empty, because if the user push on enter that means the user want to go back.
	buttons.push_back(*build.GetButton().release());
}

void ResultMenu::Update()
{
	Core::Console::SetCursorPosition(0, 0);
	std::cout << *this;
}

bool ResultMenu::MainLoop()
{
	static bool firstCalling = true;
	if (firstCalling)
	{
		Update();
		firstCalling = false;
	}

	Core::Event event;
	Core::KeyEvent* key = nullptr;

	if (Core::EventManager::PollKeyEvent(event));
	{
		IMenu::CheckUserInput(event);
		key = Core::EventManager::ParseKeyEvent(event);

		if (key)
		{
			if (key->GetKey() == Core::KeyBoard::Key::ENTER)
			{
				firstCalling = true;
				return false;
			}
			Update();
		}
	}

	return true;
}