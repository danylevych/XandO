#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace Core
{
	class FileManager
	{
	private:
		friend class Button;

	private:
		static void ReadTextForElement(const std::string& path, const std::string& message, std::vector<std::u16string>& dest, size_t countOfElement);
	public:
		static void ReadFile(const std::string& path, std::vector<std::string>& dest);
		static void ReadFile(const std::string& path, std::vector<std::u16string>& dest);
		static bool ReadFileS(const std::string& path, std::vector<std::string>& strs);
		static void WriteFile(const std::string& path, const std::vector<std::string>& strs);
	};
}