#include "FileManager.h"

#include "../../Exception/EventException.h"

namespace Core
{
	void FileManager::ReadTextForElement(const std::string& path, const std::string& message, std::vector<std::u16string>& dest, size_t countOfElement)
	{
		std::basic_ifstream<char16_t, std::char_traits<char16_t>> file;

		file.open(path, std::fstream::binary);

		if (!file.is_open())
		{
			throw EventException{ __FUNCTION__, std::string("Cannot open file: ") + path, 10 };
		}

		dest.resize(countOfElement);

		for (auto elem : message)
		{
			if (std::tolower(elem) == ' ')
			{
				for (size_t i = 0; i < countOfElement; i++)
				{
					dest[i] += u"   ";
				}
			}
			else
			{
				size_t startIndex = (std::tolower(elem) - 'a') * countOfElement;
				file.seekg(0);
				std::u16string str;

				for (size_t i = 0; i < startIndex; i++)
				{
					std::getline(file, str);
				}

				for (size_t i = 0; i < countOfElement; i++)
				{
					str.clear();
					std::getline(file, str);
					str.erase(str.size() - 1);
					dest[i] += str;
				}
			}
		}

		file.close();
	}
	void FileManager::ReadFile(const std::string& path, std::vector<std::string>& dest)
	{
		std::ifstream file;

		file.open(path);

		if (!file.is_open())
		{
			throw EventException{ __FUNCTION__, std::string("Cannot open file: ") + path, 10 };
		}

		while (!file.eof())
		{
			std::string str;
			std::getline(file, str);
			dest.push_back(str);
		}

		file.close();
	}
	void FileManager::ReadFile(const std::string& path, std::vector<std::u16string>& dest)
	{
		std::basic_ifstream<char16_t, std::char_traits<char16_t>> file;

		file.open(path, std::fstream::binary);

		if (!file.is_open())
		{
			throw EventException{ __FUNCTION__, std::string("Cannot open file: ") + path, 10 };
		}

		std::u16string ws;
		while (!file.eof())
		{
			ws.clear();
			std::getline(file, ws);
			dest.push_back(ws);
		}

		file.close();
	}
	bool FileManager::ReadFileS(const std::string& path, std::vector<std::string>& str)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			return false;
		}
		
		while (file.good())
		{
			std::string sourse;
			std::getline(file, sourse);
			str.push_back(sourse);
		}
		
		file.close();
		return true;
	}
	void FileManager::WriteFile(const std::string& path, const std::vector<std::string>& str)
	{
		std::ofstream file(path);
		if (!file.is_open())
		{
			throw EventException{ __FUNCTION__, std::string("Cannot open file: ") + path, 10 };
		}
		
		for (const auto& ele : str)
		{
			file << ele << std::endl;
		}

		file.close();
	}
}