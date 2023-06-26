#include "Wallpaper.h"


#include "../../Managers/File Manager/FileManager.h"
#include <codecvt>

namespace Core
{
	Wallpaper::Wallpaper() : wallpaper(), path() {	}
	Wallpaper::Wallpaper(const std::string& wallPath)
	{
		path = wallPath;
		FileManager::ReadFile(path, wallpaper);
	}

	void Wallpaper::Refresh()
	{
		FileManager::ReadFile(path, wallpaper);
	};
	void Wallpaper::SetWall(const std::string& wallPath)
	{
		path = wallPath;
		FileManager::ReadFile(path, wallpaper);
	}
	
	std::vector<std::u16string> Wallpaper::GetWallpaper() { return wallpaper; }

	std::ostream& operator<<(std::ostream& out, const Wallpaper& wall)
	{
		std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
		for (const auto& elem : wall.wallpaper)
		{
			if (elem != *(--wall.wallpaper.end()))
			{
				out << convert.to_bytes(elem) << std::endl;
			}
			else
			{
				out << convert.to_bytes(elem);
			}
		}
		return out;
	}
}