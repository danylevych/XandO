#pragma once

#include "Button.h"
#include "Wallpaper.h"
#include "../../Enums/Color.h"
#include "../../Event/Event.h"

namespace Core
{
	class IMenu
	{
	protected:
		Wallpaper wall;
		std::vector<Button> buttons;
		int32_t select;

	protected:
		Color user;
		Color application;
		Color background;

	protected:
		IMenu();
		IMenu(const Wallpaper& wall, const std::vector<Button>& buttons,
			Color user = Color::DARK_RED,
			Color application = Color::WHITE,
			Color background = Color::BLACK);

	public:
		virtual void Init() = 0;
		virtual bool MainLoop() = 0;

		void CheckUserInput(Event& e);
		void SetUseColor(Color color);
		void SetApplicationColor(Color color);

		Color GetUserColor() const;
		Color GetApplicationColor() const;

	public:
		virtual	~IMenu() = default;
		friend std::ostream& operator<<(std::ostream& out, const IMenu& menu);
	};
}