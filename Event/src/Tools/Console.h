#pragma once


#include <wtypes.h>
#include <string>
#include "../Enums/Color.h"

namespace Core
{
	class Console
	{
	private:
		static void ConsolePanel(int64_t type);

	private:
		static HANDLE handle;

	public:
		static void ConsoleSize(int width, int height);
		static void SetTitle(const std::wstring& title);

		static void SetTextColor(Color color);
		static void SetBackgroundColor(Color color);

		static void CursorVisible(bool visible = true);
		static void ScrollbarVisible(bool visible = true);

		static void MimMaxButton(bool canPress = true);
		static void MiniMizeButon(bool canPress = true);
		static void CloseButton(bool canPress);

		static void SetCursorPosition(int x, int y);
		static void Clear();
	};
}