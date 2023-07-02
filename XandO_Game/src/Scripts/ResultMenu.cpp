#include "ResultMenu.h"

#include <iostream>
#include <string>


ResultMenu::ResultMenu()
	: IMenu(),
	result('n')
{
	Init();
};

ResultMenu::ResultMenu(char result)
	: IMenu(),
	result(result)
{
	Init();
};

void ResultMenu::Init()
{
	this->user = Core::Color::DARK_RED;
	this->application = Core::Color::GREEN;

	std::string path = "data/Walls/ResultMenus/ResultMenu" + std::string(1, std::toupper(result)) + ".txt";
	wall = Core::Wallpaper(path);

	Core::BuildButton build;

	build.CreateButton();
	build.SetText("back", Core::Fonts::FULL);
	build.SetX(5).SetY(10);
	build.SetCommand([]() {});  // This is empty, because if the user push on enter that means the user want to go back.
	buttons.push_back(*build.GetButton().release());
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

void ResultMenu::Update()
{
	Core::Console::SetCursorPosition(0, 0);
	std::cout << *this;
}