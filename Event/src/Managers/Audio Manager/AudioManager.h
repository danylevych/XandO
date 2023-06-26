#pragma once

#include <string>

namespace Core
{
	class AudioManager
	{
	public:
		static void OpenAudio(const std::wstring& path);
		static void CloseAudio(const std::wstring& path);
		static void PlayAudio(const std::wstring& path, bool repeat = false);
	};
}