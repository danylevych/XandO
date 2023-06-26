#include "Button.h"

#include <fstream>
#include <codecvt>
#include "../Console.h"
#include "../../Exception/EventException.h"
#include "../../Managers/File Manager/FileManager.h"

namespace Core
{
	Button::Button()
		: x(0), y(0),
		isPressed(false),
		text(),
		command()
	{	}
	Button::Button(int x, int y, std::vector<std::u16string> text, std::function<void()> command, bool isPressed)

		: x(x), y(y),
		text(text),
		command(command),
		isPressed(isPressed)
	{	}

	Button::Button(Button&& other) noexcept
	{
		x = other.x;
		y = other.y;
		isPressed = other.isPressed;
		text = std::move(other.text);
		command = std::move(other.command);

		other.x = 0;
		other.y = 0;
		other.isPressed = false;
	}

	Button& Button::operator=(Button&& other) noexcept
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			isPressed = other.isPressed;
			text = std::move(other.text);
			command = std::move(other.command);

			other.x = 0;
			other.y = 0;
			other.isPressed = false;
		}

		return *this;
	}

	void Button::SetX(int x) { this->x = x; }
	void Button::SetY(int y) { this->y = y; }
	void Button::SetIsPressed(bool isPressed)
	{
		if (isPressed)
		{
			command();
			isPressed = false;
		}
		this->isPressed = isPressed;
	}

	void Button::SetText(const std::vector<std::u16string>& text) { this->text = text; }

	void Button::SetText(const std::string& message, Fonts font)
	{
		text.clear();
		FileManager::ReadTextForElement((font == Fonts::EMPTY ? R"(..\Event\data\Fonts\EmptyFont.txt)" :
																R"(..\Event\data\Fonts\FullFont.txt)"),
																message, text, (font == Fonts::EMPTY ? 6 : 3));
	}
	void Button::SetCommand(const std::function<void()>& command) { this->command = command; }

	int Button::GetX() const { return x; }
	int Button::GetY() const { return y; }
	bool Button::GetIsPressed() const { return isPressed; }
	std::vector<std::u16string> Button::GetText() const { return text; }
	std::function<void()> Button::GetCommand() const { return command; }

	std::ostream& operator<<(std::ostream& out, const Button& button)
	{
		std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;

		int temp = button.y;
		for (const auto& elem : button.text)
		{
			Console::SetCursorPosition(button.x, temp++);
			out << convert.to_bytes(elem) << std::endl;
		}

		return out;
	}
}