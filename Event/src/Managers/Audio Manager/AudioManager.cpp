#include "AudioManager.h"

#include <sstream>
#include <Windows.h>
#include "../../Exception/EventException.h"

#pragma comment(lib, "Winmm.lib")

namespace Core
{
	void AudioManager::OpenAudio(const std::wstring& path)
	{
		if (mciSendStringW((std::wstring(L"open ") + path).data(), nullptr, 0, nullptr))
		{
			auto stream = std::stringstream{};
			stream << "Cannot open media file: " << path.data();
			throw EventException{ __FUNCTION__, stream.str(), 12 };
		}
	}

	void AudioManager::CloseAudio(const std::wstring& path)
	{
		if (mciSendStringW((std::wstring(L"close ") + path).data(), nullptr, 0, nullptr))
		{
			auto stream = std::stringstream{};
			stream << "Cannot open media file: " << path.data();
			throw EventException{ __FUNCTION__, stream.str(), 12 };
		}
	}

	void AudioManager::PlayAudio(const std::wstring& path, bool repeat)
	{
		if (mciSendStringW((std::wstring(L"play ") + path + (repeat ? L" repeat" : L"")).data(), nullptr, 0, nullptr))
		{
			auto stream = std::stringstream{};
			stream << "Cannot open media file: " << path.data();
			throw EventException{ __FUNCTION__, stream.str(), 12 };
		}
	}
}