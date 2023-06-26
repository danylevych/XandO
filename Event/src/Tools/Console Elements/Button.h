#pragma once

#include <string>
#include <vector>
#include <functional>

#include "../../Enums/Letter.h"

namespace Core
{
	class Button
	{
	private:
		int x;
		int y;
		bool isPressed;
		std::vector<std::u16string> text;
		std::function<void()> command;

	public:
		friend class BuildButton;

	public:
		Button();
		Button(int x, int y, std::vector<std::u16string> text, std::function<void()> command, bool isPressed = false);

		Button(const Button& other) = default;
		Button(Button&& other) noexcept;

	public:
		Button& operator=(const Button& other) = default;
		Button& operator=(Button&& other) noexcept;

	public:
		~Button() = default;

	public:
		void SetX(int x);
		void SetY(int y);
		void SetIsPressed(bool isPressed);
		void SetText(const std::vector<std::u16string>& text);
		void SetText(const std::string& message, Fonts font = Fonts::EMPTY);
		void SetCommand(const std::function<void()>& command);
	
	public:
		int GetX() const;
		int GetY() const;
		bool GetIsPressed() const;
		std::vector<std::u16string> GetText() const;
		std::function<void()> GetCommand() const;

	public:
		friend std::ostream& operator<<(std::ostream& out, const Button& button);
	};
}