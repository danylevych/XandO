#include "BuildButton.h"

namespace Core
{
	void BuildButton::CreateButton()
	{
		button = (std::make_unique<Button>());
	}

	std::unique_ptr<Button> BuildButton::GetButton()
	{
		return std::move(button);
	}

	BuildButton& BuildButton::SetX(int x)
	{
		button->x = x;
		return *this;
	}

	BuildButton& BuildButton::SetY(int y)
	{
		button->y = y;
		return *this;
	}

	BuildButton& BuildButton::SetIsPressed(bool isPressed)
	{
		button->isPressed = isPressed;
		return *this;
	}

	BuildButton& BuildButton::SetText(const std::vector<std::u16string>& text)
	{
		button->text = text;
		return *this;
	}

	BuildButton& BuildButton::SetText(const std::string& text, Fonts font)
	{
		button->SetText(text, font);
		return *this;
	}

	BuildButton& BuildButton::SetCommand(const std::function<void()>& command)
	{
		button->command = command;
		return *this;
	}
}