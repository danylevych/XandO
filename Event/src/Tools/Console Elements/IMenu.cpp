#include "IMenu.h"

#include "../Console.h"
#include "../../Managers/Event Manager/EventManager.h"

namespace Core
{
	IMenu::IMenu()
		: wall(wall),
		buttons(buttons),
		select(0),
		user(Color::DARK_RED),
		application(Color::WHITE),
		background(Color::BLACK)
	{	}
	IMenu::IMenu(const Wallpaper& wall, const std::vector<Button>& buttons,
		Color user, Color application, Color background)
		: wall(wall),
		buttons(buttons),
		select(0),
		user(user),
		application(application),
		background(background)
	{	}


	void IMenu::CheckUserInput(Event& e)
	{
		if (e.GetType() != Event::EventType::NONE)
		{
			auto key = EventManager::ParseKeyEvent(e);
			if (key->GetIsPressed())
			{
				if (buttons.at(0).GetY() != buttons.at(buttons.size() - 1).GetY())
				{
					switch (key->GetKey())
					{
					case Core::KeyBoard::Key::ENTER:
						buttons[select].SetIsPressed(true);
						break;

					case Core::KeyBoard::Key::UP:
						select > 0 ? select-- : select = buttons.size() - 1;
						break;

					case Core::KeyBoard::Key::DOWN:
						select < buttons.size() - 1 ? select++ : select = 0;
						break;
					}
				}
				else if (buttons.at(0).GetX() != buttons.at(buttons.size() - 1).GetX())
				{
					switch (key->GetKey())
					{
					case Core::KeyBoard::Key::ENTER:
						buttons[select].SetIsPressed(true);
						break;

					case Core::KeyBoard::Key::LEFT:
						select > 0 ? select-- : select = buttons.size() - 1;
						break;

					case Core::KeyBoard::Key::RIGHT:
						select < buttons.size() - 1 ? select++ : select = 0;
						break;
					}
				}
			}
		}
	}


	void IMenu::SetUseColor(Color color) { this->user = color; }
	void IMenu::SetApplicationColor(Color color) { this->application = color; }

	Color IMenu::GetUserColor() const { return user; }
	Color IMenu::GetApplicationColor() const { return application; }


	std::ostream& operator<<(std::ostream& out, const IMenu& menu)
	{
		Console::SetTextColor(menu.application); out << menu.wall;

		for (size_t i = 0; i < menu.buttons.size(); i++)
		{
			Console::SetTextColor(menu.application);
			if (i == menu.select)
			{
				Console::SetTextColor(menu.user); out << menu.buttons[i]; Console::SetTextColor(menu.application);
			}
			else
			{
				out << menu.buttons[i];
			}
		}

		return out;
	}
}