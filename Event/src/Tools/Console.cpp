#include "Console.h"

#include <wtypes.h>
#include <string>

namespace Core
{
	HANDLE Console::handle = GetStdHandle(STD_OUTPUT_HANDLE);

	void Console::ConsolePanel(int64_t type)
	{
		HWND hwnd = GetConsoleWindow();
		LONG style = GetWindowLong(hwnd, GWL_STYLE);
		style &= ~(type);
		SetWindowLong(hwnd, GWL_STYLE, style);
	}


	void Console::ConsoleSize(int width, int height)
	{
		SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
		COORD bufferSize = { width, height };

		SetConsoleWindowInfo(handle, 1, &windowSize);
		SetConsoleScreenBufferSize(handle, bufferSize);
	}

	void Console::SetTitle(const std::wstring& title)
	{
		SetConsoleTitleW(title.data());
	}

	void Console::SetTextColor(Color color)
	{
		SetConsoleTextAttribute(handle, static_cast<int16_t>(color));
	}

	void Console::SetBackgroundColor(Color color)
	{
		int code = static_cast<int>(color);
		SetConsoleTextAttribute(handle, code << 4);
	}

	void Console::CursorVisible(bool visible)
	{
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(handle, &cci);
		cci.bVisible = visible;
		SetConsoleCursorInfo(handle, &cci);
	}

	void Console::ScrollbarVisible(bool visible)
	{
		ShowScrollBar(GetConsoleWindow(), SB_BOTH, visible);
	}

	void Console::MimMaxButton(bool canPress)
	{
		if (!canPress)
		{
			ConsolePanel(WS_MAXIMIZEBOX);
		}
	}

	void Console::MiniMizeButon(bool canPress)
	{
		if (!canPress)
		{
			ConsolePanel(WS_MINIMIZEBOX);
		}
	}

	void Console::CloseButton(bool canPress)
	{
		if (!canPress)
		{
			HWND hwnd = GetConsoleWindow();
			HMENU hmenu = GetSystemMenu(hwnd, FALSE);
			EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
		}
	}

	void Console::SetCursorPosition(int x, int y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void Console::Clear()
	{
		system("cls");
	}
}