#pragma once

#include <string>
#include <memory>
#include "../Enums/Letter.h"
#include "Console Elements/Button.h"

namespace Core
{
	class BuildButton
	{
	private:
		std::unique_ptr<Button> button = nullptr;

	public:
		void CreateButton();
		std::unique_ptr<Button> GetButton();

	public:
		BuildButton& SetX(int x = 0);
		BuildButton& SetY(int y = 0);
		BuildButton& SetIsPressed(bool isPressed = false);
		BuildButton& SetText(const std::vector<std::u16string>& text);
		BuildButton& SetText(const std::string& text, Fonts font = Fonts::FULL);
		BuildButton& SetCommand(const std::function<void()>& command);
	};
}